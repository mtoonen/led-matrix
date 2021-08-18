#include <MatrixMeine.h>

#define CLK A4
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2
#define D A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
MatrixMeine::MatrixMeine()
{
}

void MatrixMeine::initMatrix()
{
  matrix.begin();
  textX = matrix.width();
  isBusy = false;
}

void MatrixMeine::setLoading(double percentage)
{
  setLoading(percentage, "Load");
}

void MatrixMeine::setLoading(double percentage, String loadText)
{
  Serial.print("percentage:");
  Serial.println(percentage);
  Serial.print("loadText:");
  Serial.println(loadText);
  matrix.fillScreen(0);
  matrix.setCursor(6, 0);
  matrix.print(loadText);
  matrix.drawRect(xBox, yBox, widthBox, heightBox, matrix.Color333(7, 7, 0));
  int num = ((int)percentage / (100 / widthFill) + 1);
  matrix.fillRect(xBox + 1, yBox + 1, min(num, widthFill), heightFill, matrix.Color333(7, 0, 0));
  delay(100);
}

bool MatrixMeine::process()
{
  if (this->current != NULL)
  {
    switch (this->current->type)
    {
    case TEXT:
      drawText(this->current);
      break;
    case TEXT_SCROLLING:
      scrollText(this->current);
      break;
    case SHAPE:
      drawShape(this->current);
      break;
    default:
      return false;
    }
  }
  return true;
}

void MatrixMeine::drawShape(LedMessage *msg)
{
  Serial.println("drawShape" + msg->processed);
  isBusy = false;
}

void MatrixMeine::drawText(LedMessage *msg)
{
  if (!msg->shown)
  {
    matrix.setTextWrap(true); // Allow text to run off right edge
    Serial.println("Drawtext" + msg->processed);
    matrix.fillScreen(0);

    matrix.setCursor(0,12);
    matrix.print(msg->payload);
    msg->shown = true;
    isBusy = false;
  }
}

void MatrixMeine::scrollText(LedMessage *msg)
{
  matrix.fillScreen(0);
  if (!msg->shown)
  {
    textMin = msg->payload.length() * -6;
    Serial.print("Textmin:");
    Serial.println(textMin);
    msg->shown = true;
    matrix.setTextWrap(false);
    matrix.setCursor(0,12);
  }

  matrix.setCursor(textX, 12);
  matrix.print(msg->payload);

  if ((--textX) < textMin)
  {
    textX = matrix.width();
    isBusy = false;
  }
  else
  {
    isBusy = true;
  }
}

void MatrixMeine::setMessage(LedMessage *msg)
{
  if (msg != NULL)
  {
    this->current = msg;
    matrix.setTextColor(matrix.Color888(msg->r, msg->g, msg->b, false));
  }
}
