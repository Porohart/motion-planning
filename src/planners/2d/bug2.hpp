#pragma once

#include "Planner.hpp"

class Bug2 : public Planner {
    public:
        Bug2(Grid& grid, PointRobot& robot);
        virtual ~Bug2() = default;
        
        // Override virtual functions from Planner
        virtual void plan() override;
        virtual point getNextMove() override;
    private:
        // Bug2 specific state
        bool on_m_line;  // Whether robot is on the M-line (direct line from start to goal)
        point m_line_start;
        point m_line_goal;
};

