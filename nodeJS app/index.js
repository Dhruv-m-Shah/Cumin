import util from "util";
import fs from "fs";
var source = fs.readFileSync('../function1.js');
const env = {
    memoryBase: 0,
    tableBase: 0,
    memory: new WebAssembly.Memory({
      initial: 256
    }),
    table: new WebAssembly.Table({
      initial: 0,
      element: 'anyfunc'
    })
  }

var typedArray = new Uint8Array(source);

WebAssembly.instantiate(typedArray, {
  env: env
}).then(result => {
  console.log(util.inspect(result, true, 0));
  console.log(result.instance.exports._interpretorWrapper("start x = 2? end"));
}).catch(e => {
  // error caught
  console.log(e);
});