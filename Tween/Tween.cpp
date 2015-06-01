#include "Arduino.h"
#include "Tween.h"

Tween::Tween(int startValue, int endValue, unsigned int duration, unsigned int delay){
	_stateBitList = 0;
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = delay;
	_currentTime = 0;
	_cursor = 0;
	_ended(false);
	_ready(true);
	_pause(false);
	_loop(false);
	_loopWithDelay(false);
	_loopDelay = 0;
	_reverseLoop(false);
	_currentLoopReversed(false);
	_isFirstLoop(true);
}

Tween::Tween(int startValue, int endValue, unsigned int duration){
	_stateBitList = 0;
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = 0;
	_currentTime = 0;
	_cursor = 0;
	_ended(false);
	_ready(true);
	_pause(false);
	_loop(false);
	_loopWithDelay(false);
	_loopDelay = 0;
	_reverseLoop(false);
	_currentLoopReversed(false);
	_isFirstLoop(true);
}

Tween::Tween(){
	_stateBitList = 0;
	_startValue = 0;
	_endValue = 0;
	_duration = 0;
	_delay = 0;
	_currentTime = 0;
	_cursor = 0;
	_ended(false);
	_ready(false);
	_pause(false);
	_loop(false);
	_loopWithDelay(false);
	_loopDelay = 0;
	_reverseLoop(false);
	_currentLoopReversed(false);
	_isFirstLoop(true);
}

void Tween::update(unsigned int deltaTime){
	int temp;

	if (_ready() && !_ended())
	{
		_currentTime += _pause() ? 0 : deltaTime;
		if (_currentTime > _delay)
		{
			_cursor = (float)(_currentTime - _delay)/(float)_duration;
		}

		if (_currentTime >= _duration+_delay){
			_cursor = 1;
			_currentTime = _duration+_delay;
			_ended(true);

			if(_loop()){
				_ended(false);
				_ready(true);
				_currentTime = 0;
				_delay = _loopWithDelay() ? _loopDelay : _delay;

				if (_reverseLoop())
				{
					_currentLoopReversed(!_currentLoopReversed());
				}

				_isFirstLoop(false);
			}
		}
	}
}

void Tween::reverseLoop(){
	_reverseLoop(true);
}

void Tween::normalLoop(){
	_reverseLoop(false);
}

void Tween::transition(int startValue, int endValue, unsigned int duration, unsigned int delay){
	_stateBitList = 0;
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = delay;
	_currentTime = 0;
	_cursor = 0;
	_ended(false);
	_ready(true);
	_loop(false);
	_loopWithDelay(false);
	_loopDelay = 0;
	_reverseLoop(false);
	_currentLoopReversed(false);
	_isFirstLoop(true);
}

void Tween::loop(){
	_loop(true);
	_loopWithDelay(false);
	_reverseLoop(false);
	_currentLoopReversed(false);
}

void Tween::loopWithDelay(){
	loopWithDelay(_delay);
}

void Tween::loopWithDelay(unsigned int delay){
	_loop(true);
	_loopWithDelay(true);
	_loopDelay = delay;
	_reverseLoop(false);
	_currentLoopReversed(false);
}

boolean Tween::isFirstLoop(){
	return _isFirstLoop();
}

boolean Tween::isEnded(){
	return _ended();
}

void Tween::stopLoop(){
	_loop(false);
}

void Tween::pause(){
	_pause(true);
}

void Tween::play(){
	_pause(false);
}

void Tween::toggle(){
	_pause() ? play() : pause();
}

void Tween::reset(){
	_currentTime = _delay;
	_ended(false);
}

void Tween::replay(){
	reset();
	play();
}

void Tween::replayWithDelay(unsigned int delay){
	_delay = delay;
	replayWithDelay();
}

void Tween::replayWithDelay(){
	resetWithDelay();
	play();
}

void Tween::resetWithDelay(unsigned int delay){
	_delay = delay;
	resetWithDelay();
}

void Tween::resetWithDelay(){
	_currentTime = 0;
	_ended(false);
}

void Tween::stop(boolean restartBeforeDelay){
	pause();
	restartBeforeDelay ? resetWithDelay() : reset();
}

void Tween::stop(){
	stop(false);
}

void Tween::transition(int startValue, int endValue, unsigned int duration){
	transition(startValue, endValue, duration, 0);
}

void Tween::transitionTo(int endValue, unsigned int duration){
	transition((int)linearValue(), endValue, duration);
}

void Tween::transitionTo(int endValue){
	transitionTo(endValue, (_ended() ? 0 : (_duration+_delay) - _currentTime));
}

long Tween::_applyEaseFactor(float _easeFactor){
	return (long)((float)_startValue+(_easeFactor*(float)(_endValue - _startValue)));
}

/*=======================*/

long Tween::linearValue(){
	return _applyEaseFactor(linearCursor());
};
long Tween::easeInQuadValue(){
	return _applyEaseFactor(easeInQuadCursor());
};
long Tween::easeOutQuadValue(){
	return _applyEaseFactor(easeOutQuadCursor());
};
long Tween::easeInOutQuadValue(){
	return _applyEaseFactor(easeInOutQuadCursor());
};
long Tween::easeInCubicValue(){
	return _applyEaseFactor(easeInCubicCursor());
};
long Tween::easeOutCubicValue(){
	return _applyEaseFactor(easeOutCubicCursor());
};
long Tween::easeInOutCubicValue(){
	return _applyEaseFactor(easeInOutCubicCursor());
};
long Tween::easeInQuartValue(){
	return _applyEaseFactor(easeInQuartCursor());
};
long Tween::easeOutQuartValue(){
	return _applyEaseFactor(easeOutQuartCursor());
};
long Tween::easeInOutQuartValue(){
	return _applyEaseFactor(easeInOutQuartCursor());
};
long Tween::easeInQuintValue(){
	return _applyEaseFactor(easeInQuintCursor());
};
long Tween::easeOutQuintValue(){
	return _applyEaseFactor(easeOutQuintCursor());
};
long Tween::easeInOutQuintValue(){
	return _applyEaseFactor(easeInOutQuintCursor());
};

float Tween::_cursorReversed(){
	if (!_reverseLoop()){return _cursor;}
	boolean delayPassed = _currentTime > _delay;
	return _currentLoopReversed() ? (delayPassed ? (1.0 - _cursor) : _cursor) : (delayPassed || isFirstLoop() ? _cursor : (1.0 - _cursor));
}

float Tween::linearCursor(){
	return easeNone(_cursorReversed());
}

float Tween::easeInQuadCursor(){
	return easeInQuad(_cursorReversed());
}

float Tween::easeOutQuadCursor(){
	return easeOutQuad(_cursorReversed());
}

float Tween::easeInOutQuadCursor(){
	return easeInOutQuad(_cursorReversed());
}

float Tween::easeInCubicCursor(){
	return easeInCubic(_cursorReversed());
}

float Tween::easeOutCubicCursor(){
	return easeOutCubic(_cursorReversed());
}

float Tween::easeInOutCubicCursor(){
	return easeInOutCubic(_cursorReversed());
}

float Tween::easeInQuartCursor(){
	return easeInQuart(_cursorReversed());
}

float Tween::easeOutQuartCursor(){
	return easeOutQuart(_cursorReversed());
}

float Tween::easeInOutQuartCursor(){
	return easeInOutQuart(_cursorReversed());
}

float Tween::easeInQuintCursor(){
	return easeInQuint(_cursorReversed());
}

float Tween::easeOutQuintCursor(){
	return easeOutQuint(_cursorReversed());
}

float Tween::easeInOutQuintCursor(){
	return easeInOutQuint(_cursorReversed());
}

float Tween::easeNone(float t){
	return t;
}
float Tween::easeInQuad(float t){
	return t*t;
}
float Tween::easeOutQuad(float t){
	return t*(2.00-t);
}
float Tween::easeInOutQuad(float t){
	return t<0.50 ? 2.00*t*t : -1.00+(4.00-2.00*t)*t;
}
float Tween::easeInCubic(float t){
	return t*t*t;
}
float Tween::easeOutCubic(float t){
	return (--t)*t*t+1.00;
}
float Tween::easeInOutCubic(float t){
	return t<0.50 ? 4.00*t*t*t : (t-1.00)*(2.00*t-2.00)*(2.00*t-2.00)+1.00;
}
float Tween::easeInQuart(float t){
	return t*t*t*t;
}
float Tween::easeOutQuart(float t){
	return 1-(--t)*t*t*t;
}
float Tween::easeInOutQuart(float t){
	return t<0.50 ? 8.00*t*t*t*t : 1.00-8.00*(--t)*t*t*t;
}
float Tween::easeInQuint(float t){
	return t*t*t*t*t;
}

float Tween::easeOutQuint(float t){
	return 1.00+(--t)*t*t*t*t;
}

float Tween::easeInOutQuint(float t){
	return t<0.50 ? 16.00*t*t*t*t*t : 1.00+16.00*(--t)*t*t*t*t;
}

boolean Tween::_ended(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_ENDED);
}
boolean Tween::_ready(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_READY);
}
boolean Tween::_pause(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_PAUSE);
}
boolean Tween::_loop(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_LOOP);
}
boolean Tween::_loopWithDelay(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_LOOP_WITH_DELAY);
}
boolean Tween::_reverseLoop(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_REVERSE_LOOP);
}
boolean Tween::_currentLoopReversed(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_CURRENT_LOOP_REVERSED);
}
boolean Tween::_isFirstLoop(){
	return (boolean)bitRead(_stateBitList, TWEEN_STATE_BIT_IS_FIRST_LOOP);
}

void Tween::_ended(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_ENDED, (newValue ? 1 : 0));
}
void Tween::_ready(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_READY, (newValue ? 1 : 0));
}
void Tween::_pause(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_PAUSE, (newValue ? 1 : 0));
}
void Tween::_loop(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_LOOP, (newValue ? 1 : 0));
}
void Tween::_loopWithDelay(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_LOOP_WITH_DELAY, (newValue ? 1 : 0));
}
void Tween::_reverseLoop(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_REVERSE_LOOP, (newValue ? 1 : 0));
}
void Tween::_currentLoopReversed(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_CURRENT_LOOP_REVERSED, (newValue ? 1 : 0));
}
void Tween::_isFirstLoop(boolean newValue){
	bitWrite(_stateBitList, TWEEN_STATE_BIT_IS_FIRST_LOOP, (newValue ? 1 : 0));
}