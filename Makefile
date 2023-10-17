.PHONY: format-lua
format-lua:
	@find example -iname '*.lua' | xargs lua-format -c .lua-format -i
	@find test -iname '*.lua' | xargs lua-format -c .lua-format -i
	@find tool -iname '*.lua' | xargs lua-format -c .lua-format -i

.PHONY: check
check:
	@pre-commit run --all-files
