void updateDisplay(long pos) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  char posS[4]; // buffer for temp incl. decimal point & possible minus sign
  String posString = "";
  dtostrf(pos, 4, 2, posS); // Min. 6 chars wide incl. decimal point, 2 digits right of decimal//convert chararray to string
  for (int i = 0; i < sizeof(posS); i++)
  {
    posString += posS[i];
  }
  display.print("Position: ");
  display.print(posString);

  display.setCursor(0, 32);
  display.print(stepper1.currentPosition());
  display.display();
}
