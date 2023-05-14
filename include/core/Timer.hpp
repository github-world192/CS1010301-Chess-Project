/**
 *  File: Timer.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/15 00:41:49
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/15 01:37:22
 *  Description: Timer Class
 */

#pragma once

#include <chrono>
#include <ctime>

namespace Chess
{

    class Timer
    {
    private:
        time_t _time;
        time_t _offset{0};
        bool _pause{true};

    public:
        Timer()
        {
            auto now = std::chrono::system_clock::now();
            this->_time = std::chrono::system_clock::to_time_t(now);
        }

        inline time_t get() const
        {
            if ( this->_pause )
                return this->_offset;
            else
                return (Timer::_getNowTimeT() - this->_time) + this->_offset;
        }

        inline bool isPaused() const { return (this->_pause); }

        inline void start()
        {
            if ( !(this->_pause) )
                return;

            auto now = std::chrono::system_clock::now();
            this->_time = std::chrono::system_clock::to_time_t(now);
            this->_pause = false;
        }

        inline void pause()
        {
            if ( this->_pause )
                return;

            this->_offset += Timer::_getNowTimeT() - this->_time;
            this->_pause = true;
        }

        inline void reset()
        {
            this->_time = 0;
            this->_offset = 0;
            this->_pause = true;
        }

    private:
        static inline time_t _getNowTimeT()
        {
            auto now = std::chrono::system_clock::now();
            return std::chrono::system_clock::to_time_t(now);
        }
    };

}