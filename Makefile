.PHONY: format-lua
format-lua:
	@find examples -iname '*.lua' | xargs lua-format -c .lua-format -i
	@find tests -iname '*.lua' | xargs lua-format -c .lua-format -i
	@find tools -iname '*.lua' | xargs lua-format -c .lua-format -i

.PHONY: check
check:
	@pre-commit run --all-files
