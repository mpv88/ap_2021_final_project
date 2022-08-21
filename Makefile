default: all

all: 
	+$(MAKE) $@ -C c++

clean:
	+$(MAKE) $@ -C c++
	@find . -type f \( -name '*~' -o -name 'a.out' \) -exec rm '{}' \;

format:
	+$(MAKE) $@ -C c++

.PHONY: all clean format default