# SPDX-License-Identifier: BSD-3-Clause

ifneq ($(BUILD_ALL_TOOLS)$(CONFIG_USE_AMDFWTOOL),)

amdfwtoolobj = amdfwtool.o data_parse.o signed_psp.o handle_file.o
amdfwreadobj = amdfwread.o

AMDFWTOOLCFLAGS :=-O2 -Wall -Wextra -Wshadow -Werror
AMDFWTOOLCFLAGS += -I $(top)/src/commonlib/bsd/include
AMDFWTOOLCFLAGS += -D_GNU_SOURCE # memmem() from string.h

HOSTPKGCONFIG ?= pkg-config

AMDFWTOOLCFLAGS += $(shell $(HOSTPKGCONFIG) --cflags libcrypto)
ifneq ($(.SHELLSTATUS),0)
$(error "Ensure that pkg-config is installed.")
endif
LDFLAGS += $(shell $(HOSTPKGCONFIG) --libs libcrypto)

$(objutil)/amdfwtool/%.o: $(top)/util/amdfwtool/%.c # $(HEADER)
	$(HOSTCC) $(AMDFWTOOLCFLAGS) $(HOSTCFLAGS) -c -o $@ $<

$(objutil)/amdfwtool/amdfwtool: $(addprefix $(objutil)/amdfwtool/,$(amdfwtoolobj))
	printf "   AMDFWTOOL\n"
	$(HOSTCC) $(addprefix $(objutil)/amdfwtool/,$(amdfwtoolobj)) $(LDFLAGS) -o $@

$(objutil)/amdfwtool/amdfwread: $(addprefix $(objutil)/amdfwtool/,$(amdfwreadobj))
	printf "   AMDFWREAD\n"
	$(HOSTCC) $(addprefix $(objutil)/amdfwtool/,$(amdfwreadobj)) $(LDFLAGS) -o $@

endif # ifneq ($(BUILD_ALL_TOOLS)$(CONFIG_USE_AMDFWTOOL),)
