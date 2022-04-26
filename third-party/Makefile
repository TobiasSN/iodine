LIMINE_INSTALL := limine-install/limine-install

.PHONY: all
all: limine-install

.PHONY: limine-install
limine-install: $(LIMINE_INSTALL)

$(LIMINE_INSTALL):
	@# CFLAGS are a hack to prevent debug symbols from being generated, as they are not gitignored properly.
	$(MAKE) -C limine limine-install CFLAGS="-O2 -pipe -Wall -Wextra"
