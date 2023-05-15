/**
 *  File: MoveHistory.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/16 02:46:12
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/16 03:06:52
 *  Description: Move History Class
 */

#pragma once

#include <vector>

#include "Move.hpp"

namespace Chess
{

    class MoveHistory
    {
    private:
        std::vector<Move> _history;

    public:
        MoveHistory() {}

    public:
        inline void addStep(const Move &move)
        {
            this->_history.push_back(move);
        }

        inline std::vector<Move> getHistory(size_t start, size_t end) const
        {
            std::vector<Move> history(this->_history.begin() + start,
                                      this->_history.begin() + end);
            return history;
        }

        inline size_t stepCount() const
        {
            return this->_history.size();
        }

        inline void clear()
        {
            this->_history.clear();
        }

    public:
        inline const Move &operator[](size_t index) const
        {
            return this->_history[index];
        }
    };

}