# dcc_station_uart
simple dcc station using pico rp2040

features:
  short address
  128 speed step

commands:

  add loco 15                --- add engine 15 
  throttle 40 loco 15        --- set loco 15 speed to 40
  direction reverse loco 15  --- reverse direction of loco 15
  function 1 on loco 15      --- turn on function 1 loco 15
  function 1 off loco 15     --- turn off function 1 loco 15
