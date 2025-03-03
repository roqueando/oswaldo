#pragma once

namespace oswaldo
{

    class joint
    {
    public:
        virtual ~joint() = default;

        // Método abstrato para mover a junta
        virtual void move(int percent) = 0;
    };

} // namespace oswaldo
