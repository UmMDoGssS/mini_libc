CC := clang
READELF ?= readelf
NM ?= nm

CFLAGS ?= -O2
PLATFORM := src/platform/linux/x86_64
SMOKE := build/smoke
SMOKE_SOURCES := $(PLATFORM)/Start.s test/Smoke.c
SMOKE_HEADERS := $(PLATFORM)/Syscall.h include/mini/Types.h

.PHONY: all test

all: $(SMOKE)

$(SMOKE): $(SMOKE_SOURCES) $(SMOKE_HEADERS) Makefile | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -target x86_64-linux-gnu -std=c23 \
		-ffreestanding -nostdinc -Wall -Wextra -Wpedantic -Werror \
		-Iinclude -I$(PLATFORM) $(LDFLAGS) -nostdlib -static \
		-Wl,-e,_start $(SMOKE_SOURCES) -o $@

build:
	mkdir -p $@

test: $(SMOKE)
	./$(SMOKE) > $(SMOKE).out
	printf 'Hello, mini_libc!\n' | cmp - $(SMOKE).out
	@headers="$$(LC_ALL=C $(READELF) -lW $(SMOKE))" && \
		! printf '%s\n' "$$headers" | grep -q '^[[:space:]]*INTERP[[:space:]]'
	@dynamic="$$(LC_ALL=C $(READELF) -dW $(SMOKE))" && \
		! printf '%s\n' "$$dynamic" | grep -Fq '(NEEDED)'
	@undefined="$$(LC_ALL=C $(NM) -u $(SMOKE))" && test -z "$$undefined"
	@printf 'Smoke test passed\n'
