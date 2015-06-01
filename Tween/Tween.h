#ifndef Tween_h
#define Tween_h

#include "Arduino.h"

class Tween
{
	public:
		Tween(int startValue, int endValue, unsigned int duration, unsigned int delay);
		Tween(int startValue, int endValue, unsigned int duration);
		Tween();

		void update(unsigned int deltaTime);

		void transition(int startValue, int endValue, unsigned int duration, unsigned int delay);
		void transition(int startValue, int endValue, unsigned int duration);
		void transitionTo(int endValue, unsigned int duration);
		void transitionTo(int endValue);

		void loop();
		void loopWithDelay();
		void loopWithDelay(unsigned int delay);

		void stopLoop();
		void reverseLoop();
		void normalLoop();

		long linearValue();
  		long easeInQuadValue();
  		long easeOutQuadValue();
  		long easeInOutQuadValue();
  		long easeInCubicValue();
  		long easeOutCubicValue();
  		long easeInOutCubicValue();
  		long easeInQuartValue();
  		long easeOutQuartValue();
  		long easeInOutQuartValue();
  		long easeInQuintValue();
  		long easeOutQuintValue();
  		long easeInOutQuintValue();

  		double linearCursor();
  		double easeInQuadCursor();
  		double easeOutQuadCursor();
  		double easeInOutQuadCursor();
  		double easeInCubicCursor();
  		double easeOutCubicCursor();
  		double easeInOutCubicCursor();
  		double easeInQuartCursor();
  		double easeOutQuartCursor();
  		double easeInOutQuartCursor();
  		double easeInQuintCursor();
  		double easeOutQuintCursor();
  		double easeInOutQuintCursor();

  		double easeNone(double t);
  		double easeInQuad(double t);
  		double easeOutQuad(double t);
  		double easeInOutQuad(double t);
  		double easeInCubic(double t);
  		double easeOutCubic(double t);
  		double easeInOutCubic(double t);
  		double easeInQuart(double t);
  		double easeOutQuart(double t);
  		double easeInOutQuart(double t);
  		double easeInQuint(double t);
  		double easeOutQuint(double t);
  		double easeInOutQuint(double t);

		void pause();
		void play();
		void toggle();
		void reset();
		void replay();
		void replayWithDelay(unsigned int delay);
		void replayWithDelay();
		void resetWithDelay(unsigned int delay);
		void resetWithDelay();
		void stop(boolean restartBeforeDelay);
		void stop();

		boolean isEnded();
		boolean isFirstLoop();

	private:
		boolean _ended;
		boolean _ready;
		boolean _pause;
		boolean _loop;
		boolean _loopWithDelay;
		boolean _reverseLoop;
		boolean _currentLoopReversed;
		boolean _firstLoop;
		int _startValue;
		int _endValue;
		unsigned int _duration;
		unsigned int _delay;
		unsigned int _loopDelay;
		unsigned int _currentTime;
		double _cursor;

		double _cursorReversed();
		long _applyEaseFactor(double _easeFactor);
};

#endif