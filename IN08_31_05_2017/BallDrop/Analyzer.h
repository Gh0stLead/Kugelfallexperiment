#ifndef ANALYZER_H
#define ANALYZER_H

#include "PhotoSensorReader.h"
#include "HallSensorReader.h"

class Analyzer {
  public:
    /**
       Constructor / setup
    */
    Analyzer(PhotoSensorReader* photoSensorReader, HallSensorReader* hallSensorReader);

    //loop
    void analyzeSystem();

    bool prepareToDrop();

  private:
    //it takes the ball 500ms to fall
    const unsigned long m_ballDropTimeDelay = 500;

    unsigned long m_dropTimestamp;

	unsigned long getTimeTillNextHole();
	unsigned long getCurrentSpeed();
	unsigned long calculateTimeToWait();

    PhotoSensorReader* m_photoSensorReader;
    HallSensorReader* m_hallSensorReader;

    bool m_systemStable = false;

    unsigned long m_plateSpeedPerSegment;
    unsigned long m_lastHoleAboveTargetTimestamp;
    unsigned long m_timer;
};

#endif
