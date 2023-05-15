/**
 *  File: Timer.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/15 00:41:49
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/16 02:48:17
 *  Description: Timer Class
 */

#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace Chess
{

    class Timer
    {
    private:
        time_t _time;
        time_t _offset{0};
        bool _pause{true};

    public:
        Timer() {}
        Timer(time_t time) : _offset(time) {}

    public:
        inline void set(time_t time)
        {
            this->_time = Timer::_getNowTimeT();
            this->_offset = time;
        }

        inline time_t get() const
        {
            if ( this->_pause )
                return this->_offset;
            else
                return (Timer::_getNowTimeT() - this->_time) + this->_offset;
        }

        inline bool isPaused() const { return this->_pause; }

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

        inline std::string str() const
        {
            return Timer::toStr(this->get());
        }

        static inline std::string toStr(time_t time)
        {
            std::stringstream ss;
            uint32_t minutes = time / 60;
            uint32_t seconds = time % 60;
            ss << std::setw(2) << std::setfill('0') << minutes
               << ':'
               << std::setw(2) << std::setfill('0') << seconds;
            return ss.str();
        }

    private:
        static inline time_t _getNowTimeT()
        {
            auto now = std::chrono::system_clock::now();
            return std::chrono::system_clock::to_time_t(now);
        }
    };

}