#include <stdio.h>
#include <string.h>
#include <vector>
#include "headers/command.h"
#include "headers/ctrlr.h"

void ctrlr::ctrlr()
{
  //  command None = new noCommand();
  command heater = new heater();  
  onCommands.push_back(heater);
  offCommands.push_back(heater);
}
void ctrlr::set(int index, command on, command off)
{
  onCommands.push_back(on);
  offCommands.push_back(off);
}
void ctrlr::on(int index)
{
  onCommands[i].execute("heater_on");
  log.push_back(onCommands[i]);
}
void ctrlr::off(int index)
{
  offCommands[i].execute("heater_off");
  log.pop(onCommands[i]);
}
