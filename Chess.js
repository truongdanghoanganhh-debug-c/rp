console.log("Chess script running");
console.log($request.url);
console.log($response.body);

if (!$response || !$response.body) {
  console.log("No response body");
  $done({});
}

let obj = JSON.parse($response.body);
obj.test = "ok";

$done({ body: JSON.stringify(obj) });
