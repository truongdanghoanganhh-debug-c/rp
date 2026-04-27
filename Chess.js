var obj = JSON.parse($response.body);

// đảm bảo có data
if (!obj.data) {
  obj.data = {};
}

let time = new Date();

// mapping kiểu “entitlement”
const premium = {
  is_premium: 1,
  type: "diamond",
  sku: "diamond_yearly_032022",
  is_apple_subscriber: true,
  start: Math.floor(time / 1000),
  expires: Math.floor(new Date(time.setFullYear(time.getFullYear() + 1)) / 1000)
};

// gán dữ liệu
obj.data.is_premium = premium.is_premium;
obj.data.type = premium.type;
obj.data.sku = premium.sku;
obj.data.is_apple_subscriber = premium.is_apple_subscriber;

// đảm bảo có date
if (!obj.data.date) {
  obj.data.date = {};
}

obj.data.date.start = premium.start;
obj.data.date.expires = premium.expires;

// debug
obj.message = "Handled by script";

$done({ body: JSON.stringify(obj) });
