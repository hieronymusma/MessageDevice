#include <Matrix/MatrixSubsystem.h>

MatrixSubsystem::MatrixSubsystem(Scheduler &scheduler) : mx{MATRIX_TYPE, SS, 1}, slidingTask{scheduler, mx}, pulsatingTask{scheduler, mx}
{
  mx.begin();
  mx.setFont(nullptr);
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 8);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

void MatrixSubsystem::slidingAnimation(const uint16_t character)
{
  pulsatingTask.stop();
  slidingTask.start(character);
}

void MatrixSubsystem::pulsatingAnimation(const uint16 character)
{
  slidingTask.stop();
  pulsatingTask.start(character);
}

void MatrixSubsystem::draw(const bool leds[64])
{
  slidingTask.stop();
  pulsatingTask.stop();
  mx.clear();

  for (int row = 0; row < 8; row++)
  {
    for (int column = 0; column < 8; column++)
    {
      int index = row * 8 + column;
      mx.setPoint(row, column, leds[index]);
    }
  }
}

void MatrixSubsystem::clear()
{
  slidingTask.stop();
  mx.clear();
}