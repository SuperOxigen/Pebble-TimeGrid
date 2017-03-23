COMPILER = pebble
PHONE = 10.133.135.87
SOURCE = src
HDRTYPE = h
SRCTYPE = c
BINARY = build
CFLAGS =

all: $(BINARY)

force:
	$(COMPILER) build $(CFLAGS)

$(BINARY): $(SOURCE)/*.$(SRCTYPE) $(SOURCE)/*.$(HDRTYPE)
	$(MAKE) force

clean:
	rm -r $(BINARY)/*

install: $(BINARY)
	$(COMPILER) install --phone $(PHONE)

emulate:
	pebble install --emulator basalt build/Pebble-TimeGrid.pbw

logs:
	$(COMPILER) logs --phone $(PHONE)
