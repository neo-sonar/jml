JML_VIEWER ?= ../../build/tool/jml-viewer/jml-viewer_artefacts/MinSizeRel/jml-viewer

.PHONY: all
all: generate

.PHONY: generate
generate: out
	${JML_VIEWER} test -s main.lua
	ldoc .

out:
	mkdir -p out
	mkdir -p out/src
	mkdir -p out/html

.PHONY: clean
clean:
	rm -rf out
