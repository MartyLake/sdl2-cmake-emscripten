.DEFAULT_GOAL := check-pkg-config

$(MAKECMDGOALS):
	cd ../build/ && $(MAKE) $(MAKECMDGOALS)

check-pkg-config:
	cd ../build_native// && cmake --build .

