include Common.mk

all:
	$(MAKE) -C cart

run:
	$(MAKE) -C cart
	$(RUN) cart/game.lnx

clean:
	$(MAKE) -C cart clean

