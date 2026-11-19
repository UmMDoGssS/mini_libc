CC := clang
READELF ?= readelf
NM ?= nm

CFLAGS ?= -O2
PLATFORM := src/platform/linux/x86_64
EXIT_DIR := src/core/Exit
SMOKE := build/smoke
EXIT_STATUS := build/exit-status
RUNTIME_SOURCES := $(PLATFORM)/Start.s $(EXIT_DIR)/Exith.c
RUNTIME_HEADERS := $(EXIT_DIR)/Exit.h $(EXIT_DIR)/ExitNoNamespace.h \
	$(PLATFORM)/Syscall.h $(PLATFORM)/SyscallNoNamespace.h \
	$(PLATFORM)/SyscallNumber.h $(PLATFORM)/SyscallNumberNoNamespace.h \
	include/mini/Types.h include/mini/TypesNoNamespace.h

.PHONY: all test

all: $(SMOKE)

$(SMOKE): test/Smoke.c
$(EXIT_STATUS): test/Exit.c

$(SMOKE) $(EXIT_STATUS): $(RUNTIME_SOURCES) $(RUNTIME_HEADERS) Makefile | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -target x86_64-linux-gnu -std=c23 \
		-ffreestanding -nostdinc -Wall -Wextra -Wpedantic -Werror \
		-Iinclude -Iinclude -Isrc $(LDFLAGS) -nostdlib -static \
		-Wl,-e,_start $(filter %.s %.c,$^) -o $@

build:
	mkdir -p $@

test: $(SMOKE) $(EXIT_STATUS)
	./$(SMOKE) > $(SMOKE).out
	printf 'Hello, mini_libc!\n' | cmp - $(SMOKE).out
	@status=0; ./$(EXIT_STATUS) || status=$$?; \
		if [ "$$status" -ne 23 ]; then \
			printf 'Expected exit status 23, got %s\n' "$$status" >&2; \
			exit 1; \
		fi
	@set -e; for binary in $^; do \
		headers="$$(LC_ALL=C $(READELF) -lW "$$binary")"; \
		dynamic="$$(LC_ALL=C $(READELF) -dW "$$binary")"; \
		undefined="$$(LC_ALL=C $(NM) -u "$$binary")"; \
		if printf '%s\n' "$$headers" | grep -q '^[[:space:]]*INTERP[[:space:]]' \
			|| printf '%s\n' "$$dynamic" | grep -Fq '(NEEDED)' \
			|| [ -n "$$undefined" ]; then \
			printf '%s has an ELF interpreter, dynamic dependencies, or unresolved symbols\n' "$$binary" >&2; \
			exit 1; \
		fi; \
	done
	@printf 'Smoke and exit status tests passed\n'
