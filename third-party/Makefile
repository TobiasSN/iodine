LIMINE_DEPLOY := limine/limine-deploy

.PHONY: all
all: limine-deploy

.PHONY: limine-deploy
limine-deploy: $(LIMINE_DEPLOY)

$(LIMINE_INSTALL):
	@# CFLAGS are a hack to prevent debug symbols from being generated, as they are not gitignored properly.
	$(MAKE) -C limine limine-deploy CFLAGS="-O2 -pipe -Wall -Wextra"
