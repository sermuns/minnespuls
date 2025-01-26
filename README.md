# minnespuls

> För att utveckla, installera `arduino-cli` och `esp-tool`. Detta görs automatiskt om du väljer att installera `mise`:

Installera [`mise`](https://mise.jdx.dev/getting-started.html)

1. `cd nodemcu`
2. `mise trust`
3. `mise install`
4. Nu finns kommandon som `mise build` och `mise prog`.
    - `mise prog` försöker ladda upp kod på `/dev/ttyUSB0`, kanske inte stämmer för din setup?
