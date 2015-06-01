#include "Arduino.h"
#include "Tween.h"

Tween::Tween(int startValue, int endValue, unsigned int duration, unsigned int delay){
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = delay;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = true;
	_pause = false;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_reverseLoop = false;
	_currentLoopReversed = false;
	_firstLoop = true;
}

Tween::Tween(int startValue, int endValue, unsigned int duration){
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = 0;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = true;
	_pause = false;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_reverseLoop = false;
	_currentLoopReversed = false;
	_firstLoop = true;
}

Tween::Tween(){
	_startValue = 0;
	_endValue = 0;
	_duration = 0;
	_delay = 0;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = false;
	_pause = false;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_reverseLoop = false;
	_currentLoopReversed = false;
	_firstLoop = true;
}

void Tween::update(unsigned int deltaTime){
	int temp;
	if (_ready && !_ended)
	{
		_currentTime += _pause ? 0 : deltaTime;
		if (_currentTime > _delay)
		{
			_cursor = (double)(_currentTime - _delay)/(double)_duration;
		}

		if (_currentTime >= _duration+_delay){
			_cursor = 1;
			_currentTime = _duration+_delay;
			_ended = true;

			if(_loop){
				_ended = false;
				_ready = true;
				_currentTime = 0;
				_delay = _loopWithDelay ? _loopDelay : _delay;

				if (_reverseLoop)
				{
					_currentLoopReversed = !_currentLoopReversed;
				}

				_firstLoop = false;
			}
		}
	}
}

void Tween::reverseLoop(){
	_reverseLoop = true;
}

void Tween::normalLoop(){
	_reverseLoop = false;
}

void Tween::transition(int startValue, int endValue, unsigned int duration, unsigned int delay){
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = delay;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = true;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_reverseLoop = false;
	_currentLoopReversed = false;
	_firstLoop = true;
}

void Tween::loop(){
	_loop = true;
	_loopWithDelay = false;
	_reverseLoop = false;
	_currentLoopReversed = false;
}

void Tween::loopWithDelay(){
	loopWithDelay(_delay);
}

void Tween::loopWithDelay(unsigned int delay){
	_loop = true;
	_loopWithDelay = true;
	_loopDelay = delay;
	_reverseLoop = false;
	_currentLoopReversed = false;
}

boolean Tween::isEnded(){
	return _ended;
}

boolean Tween::isFirstLoop(){
	return _firstLoop;
}

void Tween::stopLoop(){
	_loop = false;
}

void Tween::pause(){
	_pause = true;
}

void Tween::play(){
	_pause = false;
}

void Tween::toggle(){
	_pause ? play() : pause();
}

void Tween::reset(){
	_currentTime = _delay;
	_ended = false;
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
	_ended = false;
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
	transitionTo(endValue, (_ended ? 0 : (_duration+_delay) - _currentTime));
}

long Tween::_applyEaseFactor(double _easeFactor){
	return (long)((double)_startValue+(_easeFactor*(double)(_endValue - _startValue)));
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

double Tween::_cursorReversed(){
	if (!_reverseLoop){return _cursor;}
	boolean delayPassed = _currentTime > _delay;
	return _currentLoopReversed ? (delayPassed ? (1.0 - _cursor) : _cursor) : (delayPassed || isFirstLoop() ? _cursor : (1.0 - _cursor));
}

double Tween::linearCursor(){
	return easeNone(_cursorReversed());
}

double Tween::easeInQuadCursor(){
	return easeInQuad(_cursorReversed());
}

double Tween::easeOutQuadCursor(){
	return easeOutQuad(_cursorReversed());
}

double Tween::easeInOutQuadCursor(){
	return easeInOutQuad(_cursorReversed());
}

double Tween::easeInCubicCursor(){
	return easeInCubic(_cursorReversed());
}

double Tween::easeOutCubicCursor(){
	return easeOutCubic(_cursorReversed());
}

double Tween::easeInOutCubicCursor(){
	return easeInOutCubic(_cursorReversed());
}

double Tween::easeInQuartCursor(){
	return easeInQuart(_cursorReversed());
}

double Tween::easeOutQuartCursor(){
	return easeOutQuart(_cursorReversed());
}

double Tween::easeInOutQuartCursor(){
	return easeInOutQuart(_cursorReversed());
}

double Tween::easeInQuintCursor(){
	return easeInQuint(_cursorReversed());
}

double Tween::easeOutQuintCursor(){
	return easeOutQuint(_cursorReversed());
}

double Tween::easeInOutQuintCursor(){
	return easeInOutQuint(_cursorReversed());
}

double Tween::easeNone(double t){
	return t;
}
double Tween::easeInQuad(double t){
	return t*t;
}
double Tween::easeOutQuad(double t){
	return t*(2.00-t);
}
double Tween::easeInOutQuad(double t){
	return t<0.50 ? 2.00*t*t : -1.00+(4.00-2.00*t)*t;
}
double Tween::easeInCubic(double t){
	return t*t*t;
}
double Tween::easeOutCubic(double t){
	return (--t)*t*t+1.00;
}
double Tween::easeInOutCubic(double t){
	return t<0.50 ? 4.00*t*t*t : (t-1.00)*(2.00*t-2.00)*(2.00*t-2.00)+1.00;
}
double Tween::easeInQuart(double t){
	return t*t*t*t;
}
double Tween::easeOutQuart(double t){
	return 1-(--t)*t*t*t;
}
double Tween::easeInOutQuart(double t){
	return t<0.50 ? 8.00*t*t*t*t : 1.00-8.00*(--t)*t*t*t;
}
double Tween::easeInQuint(double t){
	return t*t*t*t*t;
}

double Tween::easeOutQuint(double t){
	return 1.00+(--t)*t*t*t*t;
}

double Tween::easeInOutQuint(double t){
	return t<0.50 ? 16.00*t*t*t*t*t : 1.00+16.00*(--t)*t*t*t*t;
}