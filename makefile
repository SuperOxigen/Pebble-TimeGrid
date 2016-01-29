COMPILER = pebble
PHONE = 10.137.135.11
SOURCE = src
HDRTYPE = h
SRCTYPE = c
BINARY = build

all: $(BINARY)

$(BINARY): $(SOURCE)/*.$(SRCTYPE) $(SOURCE)/*.$(HDRTYPE)
	$(COMPILER) build

clean:
	rm -r $(BINARY)/*

install: $(BINARY)
	$(COMPILER) install --phone $(PHONE)
