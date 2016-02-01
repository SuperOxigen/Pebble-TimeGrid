COMPILER = pebble
PHONE = 192.168.1.118
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
