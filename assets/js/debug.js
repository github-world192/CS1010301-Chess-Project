function test() {
  let data = apiTest();
  let width = data.width;
  let height = data.height;
  $("#test_message").text(`width=${width}, height=${height}`);
}
