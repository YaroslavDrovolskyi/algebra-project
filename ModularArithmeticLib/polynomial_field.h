#pragma once
#include <map>
#include "big_integers/bigint.h"
#include "polynomial_ring.h"


class polynomial_field {

    public:
        polynomial_field() = delete;

        polynomial_field(const polynomial_ring& pol) {
            if (pol.getDegree() == 0) {
                throw std::invalid_argument("invalid argument");
            }

            setIrreducible(pol);
        };

        void setIrreducible(polynomial_ring pol) {
            pol.normalize();
            if (!pol.isIrreducible())
                throw std::invalid_argument("invalid argument");
            else
                irreducible = pol;
        }


        polynomial_ring addition(const polynomial_ring& a, const polynomial_ring& b) const {
            polynomial_ring res = a + b;
            res = res.remainder(res, irreducible);
            return res;
        }

        polynomial_ring subtract(const polynomial_ring& a, const polynomial_ring& b) const {
            polynomial_ring res = a - b;

            res = res.remainder(res, irreducible);
            return res;
        }

        polynomial_ring multiply(const polynomial_ring& a, const polynomial_ring& b) const {
             polynomial_ring res = a * b;

            res = res.remainder(res, irreducible);
            return res;
        }


        polynomial_ring quickPow(const polynomial_ring& poly,bigint power) const {
            if (power < bigint(1)) {
                throw std::invalid_argument("invalid argument");
            }

            polynomial_ring result({ bigint(1) }, poly.getModulus());
            polynomial_ring multiplier = poly;

            while (!power.isZero()) {
                if (power % bigint(2) == bigint(0)) {
                    multiplier *= multiplier;
                    power /= 2;
                } else {
                    result *= multiplier;
                    --power;
                }
            }

            return result.remainder(result,irreducible);
        }

    private:
        polynomial_ring irreducible;
};
