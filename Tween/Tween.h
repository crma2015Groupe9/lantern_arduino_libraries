#ifndef Tween_h
#define Tween_h

#include "Arduino.h"

#define TWEEN_STATE_BIT_ENDED 0
#define TWEEN_STATE_BIT_READY 1
#define TWEEN_STATE_BIT_PAUSE 2
#define TWEEN_STATE_BIT_LOOP 3
#define TWEEN_STATE_BIT_LOOP_WITH_DELAY 4
#define TWEEN_STATE_BIT_REVERSE_LOOP 5
#define TWEEN_STATE_BIT_CURRENT_LOOP_REVERSED 6
#define TWEEN_STATE_BIT_IS_FIRST_LOOP 7

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

  		float linearCursor();
  		float easeInQuadCursor();
  		float easeOutQuadCursor();
  		float easeInOutQuadCursor();
  		float easeInCubicCursor();
  		float easeOutCubicCursor();
  		float easeInOutCubicCursor();
  		float easeInQuartCursor();
  		float easeOutQuartCursor();
  		float easeInOutQuartCursor();
  		float easeInQuintCursor();
  		float easeOutQuintCursor();
  		float easeInOutQuintCursor();

  		float easeNone(float t);
  		float easeInQuad(float t);
  		float easeOutQuad(float t);
  		float easeInOutQuad(float t);
  		float easeInCubic(float t);
  		float easeOutCubic(float t);
  		float easeInOutCubic(float t);
  		float easeInQuart(float t);
  		float easeOutQuart(float t);
  		float easeInOutQuart(float t);
  		float easeInQuint(float t);
  		float easeOutQuint(float t);
  		float easeInOutQuint(float t);

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

		boolean isFirstLoop();
		boolean isEnded();

		int startValue();
		int endValue();

	private:
		byte _stateBitList;
		
		boolean _ended();
		boolean _ready();
		boolean _pause();
		boolean _loop();
		boolean _loopWithDelay();
		boolean _reverseLoop();
		boolean _currentLoopReversed();
		boolean _isFirstLoop();

		void _ended(boolean newValue);
		void _ready(boolean newValue);
		void _pause(boolean newValue);
		void _loop(boolean newValue);
		void _loopWithDelay(boolean newValue);
		void _reverseLoop(boolean newValue);
		void _currentLoopReversed(boolean newValue);
		void _isFirstLoop(boolean newValue);
		
		int _startValue;
		int _endValue;
		unsigned int _duration;
		unsigned int _delay;
		unsigned int _loopDelay;
		unsigned int _currentTime;
		float _cursor;

		float _cursorReversed();
		long _applyEaseFactor(float _easeFactor);
};

#endif