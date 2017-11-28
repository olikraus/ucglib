TOPTARGETS := all clean

NOWANTS=
SUBDIRS := $(filter-out $(NOWANTS), $(wildcard */.))

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
