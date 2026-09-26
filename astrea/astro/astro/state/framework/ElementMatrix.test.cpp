/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/state/framework/ElementMatrix.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using CartesianElements   = ElementMatrix<6, 1, Distance, Distance, Distance, Velocity, Velocity, Velocity>;
using KeplerianElements   = ElementMatrix<6, 1, Distance, Unitless, Angle, Angle, Angle, Angle>;
using EquinoctialElements = ElementMatrix<6, 1, Distance, Unitless, Unitless, Unitless, Unitless, Angle>;

class ElementMatrixTest : public testing::Test {
  public:
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(ElementMatrixTest, DefaultConstructor) { ASSERT_NO_THROW(KeplerianElements()); }

TEST_F(ElementMatrixTest, ElementConstructor)
{
    ASSERT_NO_THROW(KeplerianElements(Distance{}, Unitless{}, Angle{}, Angle{}, Angle{}, Angle{}));
}

TEST_F(ElementMatrixTest, Partial)
{
    KeplerianElements elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );
    auto partialElements = KeplerianElements::partial_in<Time>(elements / Time{ 1.0 * s });
    auto weirdPartial    = KeplerianElements::partial_in<Distance>(elements / Distance{ 1.0 * km });

    static_assert(std::is_same_v<decltype(partialElements), KeplerianElements::partial_in<Time>>);
    static_assert(std::is_same_v<decltype(partialElements * Time{}), KeplerianElements>);
}

TEST_F(ElementMatrixTest, CopyConstructor)
{
    KeplerianElements elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );
    ASSERT_NO_THROW(KeplerianElements copy(elements));
    KeplerianElements copy(elements);
    ASSERT_EQ(copy.get<0>(), Distance{ 1.0 * km });
    ASSERT_EQ(copy.get<1>(), Unitless{ 1.0 * one });
    ASSERT_EQ(copy.get<2>(), Angle{ 1.0 * deg });
    ASSERT_EQ(copy.get<3>(), Angle{ 1.0 * deg });
    ASSERT_EQ(copy.get<4>(), Angle{ 1.0 * deg });
    ASSERT_EQ(copy.get<5>(), Angle{ 1.0 * deg });
}

TEST_F(ElementMatrixTest, MoveConstructor)
{
    KeplerianElements elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );
    ASSERT_NO_THROW(KeplerianElements moved(std::move(elements)));
    KeplerianElements moved(std::move(elements));
    ASSERT_EQ(moved.get<0>(), Distance{ 1.0 * km });
    ASSERT_EQ(moved.get<1>(), Unitless{ 1.0 * one });
    ASSERT_EQ(moved.get<2>(), Angle{ 1.0 * deg });
    ASSERT_EQ(moved.get<3>(), Angle{ 1.0 * deg });
    ASSERT_EQ(moved.get<4>(), Angle{ 1.0 * deg });
    ASSERT_EQ(moved.get<5>(), Angle{ 1.0 * deg });
}

TEST_F(ElementMatrixTest, ElementAccess)
{
    KeplerianElements elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );
    ASSERT_EQ(elements.get<0>(), Distance{ 1.0 * km });
    ASSERT_EQ(elements.get<1>(), Unitless{ 1.0 * one });
    ASSERT_EQ(elements.get<2>(), Angle{ 1.0 * deg });
    ASSERT_EQ(elements.get<3>(), Angle{ 1.0 * deg });
    ASSERT_EQ(elements.get<4>(), Angle{ 1.0 * deg });
    ASSERT_EQ(elements.get<5>(), Angle{ 1.0 * deg });

    const auto firstElement  = elements.get<0, 0>();
    const auto secondElement = elements.get<1, 0>();
    const auto thirdElement  = elements.get<2, 0>();
    const auto fourthElement = elements.get<3, 0>();
    const auto fifthElement  = elements.get<4, 0>();
    const auto sixthElement  = elements.get<5, 0>();

    ASSERT_EQ(firstElement, Distance{ 1.0 * km });
    ASSERT_EQ(secondElement, Unitless{ 1.0 * one });
    ASSERT_EQ(thirdElement, Angle{ 1.0 * deg });
    ASSERT_EQ(fourthElement, Angle{ 1.0 * deg });
    ASSERT_EQ(fifthElement, Angle{ 1.0 * deg });
    ASSERT_EQ(sixthElement, Angle{ 1.0 * deg });
}

TEST_F(ElementMatrixTest, RowColumnAccess)
{
    ElementMatrix<2, 3, Distance, Unitless, Angle, Angle, Angle, Angle> elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );

    auto row0 = elements.get_row<0>();
    ASSERT_EQ(row0.size, 3);
    ASSERT_EQ(row0.n_row, 1);
    ASSERT_EQ(row0.n_col, 3);
    ASSERT_EQ(row0.get<0>(), Distance{ 1.0 * km });
    ASSERT_EQ(row0.get<1>(), Unitless{ 1.0 * one });
    ASSERT_EQ(row0.get<2>(), Angle{ 1.0 * deg });

    auto col0 = elements.get_col<0>();
    ASSERT_EQ(col0.size, 2);
    ASSERT_EQ(col0.n_row, 2);
    ASSERT_EQ(col0.n_col, 1);
    ASSERT_EQ(col0.get<0>(), Distance{ 1.0 * km });
    ASSERT_EQ(col0.get<1>(), Angle{ 1.0 * deg });
}

TEST_F(ElementMatrixTest, GetSubMatrix)
{
    ElementMatrix<3, 3, Distance, Unitless, Angle, Angle, Angle, Angle, Distance, Unitless, Angle> elements(
        Distance{ 1.0 * km },
        Unitless{ 1.0 * one },
        Angle{ 1.0 * deg },
        Angle{ 2.0 * deg },
        Angle{ 3.0 * deg },
        Angle{ 4.0 * deg },
        Distance{ 5.0 * km },
        Unitless{ 6.0 * one },
        Angle{ 7.0 * deg }
    );

    auto submatrix = elements.get_submatrix<1, 3, 1, 3>();
    ASSERT_EQ(submatrix.size, 4);
    ASSERT_EQ(submatrix.n_row, 2);
    ASSERT_EQ(submatrix.n_col, 2);
    ASSERT_EQ(submatrix.get<0>(), Angle{ 3.0 * deg });
    ASSERT_EQ(submatrix.get<1>(), Angle{ 4.0 * deg });
    ASSERT_EQ(submatrix.get<2>(), Unitless{ 6.0 * one });
    ASSERT_EQ(submatrix.get<3>(), Angle{ 7.0 * deg });
}

TEST_F(ElementMatrixTest, Size)
{
    ASSERT_EQ(CartesianElements().size, 6);
    ASSERT_EQ(KeplerianElements().size, 6);
    ASSERT_EQ(EquinoctialElements().size, 6);
}

TEST_F(ElementMatrixTest, AdditionSubtraction)
{
    KeplerianElements elements1(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );
    KeplerianElements elements2(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );

    auto elementsPlus = elements1 + elements2;
    ASSERT_EQ(elementsPlus.get<0>(), Distance{ 2.0 * km });
    ASSERT_EQ(elementsPlus.get<1>(), Unitless{ 2.0 * one });
    ASSERT_EQ(elementsPlus.get<2>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsPlus.get<3>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsPlus.get<4>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsPlus.get<5>(), Angle{ 2.0 * deg });

    auto elementsMinus = elements1 - elements2;
    ASSERT_EQ(elementsMinus.get<0>(), Distance{ 0.0 * km });
    ASSERT_EQ(elementsMinus.get<1>(), Unitless{ 0.0 * one });
    ASSERT_EQ(elementsMinus.get<2>(), Angle{ 0.0 * deg });
    ASSERT_EQ(elementsMinus.get<3>(), Angle{ 0.0 * deg });
    ASSERT_EQ(elementsMinus.get<4>(), Angle{ 0.0 * deg });
    ASSERT_EQ(elementsMinus.get<5>(), Angle{ 0.0 * deg });

    elements1 += elements2;
    ASSERT_EQ(elements1, elementsPlus);

    elements1 -= elements2;
    ASSERT_EQ(elements1, elements2);
}

TEST_F(ElementMatrixTest, MultiplicationDivisionByArithmeticScalar)
{
    KeplerianElements elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );

    auto elementsTimesScalar = elements * 2.0;
    ASSERT_EQ(elementsTimesScalar.get<0>(), Distance{ 2.0 * km });
    ASSERT_EQ(elementsTimesScalar.get<1>(), Unitless{ 2.0 * one });
    ASSERT_EQ(elementsTimesScalar.get<2>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsTimesScalar.get<3>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsTimesScalar.get<4>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsTimesScalar.get<5>(), Angle{ 2.0 * deg });
    ASSERT_EQ(elementsTimesScalar, 2.0 * elements);

    auto elementsDividedByScalar = elements / 2.0;
    ASSERT_EQ(elementsDividedByScalar.get<0>(), Distance{ 0.5 * km });
    ASSERT_EQ(elementsDividedByScalar.get<1>(), Unitless{ 0.5 * one });
    ASSERT_EQ(elementsDividedByScalar.get<2>(), Angle{ 0.5 * deg });
    ASSERT_EQ(elementsDividedByScalar.get<3>(), Angle{ 0.5 * deg });
    ASSERT_EQ(elementsDividedByScalar.get<4>(), Angle{ 0.5 * deg });
    ASSERT_EQ(elementsDividedByScalar.get<5>(), Angle{ 0.5 * deg });
    ASSERT_EQ(elementsDividedByScalar, elements / 2.0);

    elements *= 2.0;
    ASSERT_EQ(elements, elementsTimesScalar);

    elements /= 2.0;
    ASSERT_EQ(
        elements,
        KeplerianElements(Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg })
    );
}

TEST_F(ElementMatrixTest, MultiplicationDivisionByUnitedScalar)
{
    KeplerianElements elements(
        Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }
    );

    Distance scale = 2.0 * km;

    auto elementsTimesScalar = elements * scale;
    ASSERT_EQ(elementsTimesScalar.get<0>(), Distance{ 1.0 * km } * scale);
    ASSERT_EQ(elementsTimesScalar.get<1>(), Unitless{ 1.0 * one } * scale);
    ASSERT_EQ(elementsTimesScalar.get<2>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(elementsTimesScalar.get<3>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(elementsTimesScalar.get<4>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(elementsTimesScalar.get<5>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(elementsTimesScalar, scale * elements);

    auto elementsDividedByScalar = elements / scale;
    ASSERT_EQ(elementsDividedByScalar.get<0>(), Distance{ 1.0 * km } / scale);
    ASSERT_EQ(elementsDividedByScalar.get<1>(), Unitless{ 1.0 * one } / scale);
    ASSERT_EQ(elementsDividedByScalar.get<2>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(elementsDividedByScalar.get<3>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(elementsDividedByScalar.get<4>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(elementsDividedByScalar.get<5>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(elementsDividedByScalar, elements / scale);
}

TEST_F(ElementMatrixTest, MatrixMultiplication)
{
    ElementMatrix<2, 3, double, double, double, double, double, double> A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    ElementMatrix<3, 2, double, double, double, double, double, double> B{ 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

    auto C = A * B;

    ASSERT_EQ(C.size, 4);
    ASSERT_EQ(C.n_row, 2);
    ASSERT_EQ(C.n_col, 2);
    ASSERT_EQ(C.get<0>(), 58.0);  // Row 1: (1*7 + 2*9 + 3*11)
    ASSERT_EQ(C.get<1>(), 64.0);  // Row 1: (1*8 + 2*10 + 3*12)
    ASSERT_EQ(C.get<2>(), 139.0); // Row 2: (4*7 + 5*9 + 6*11)
    ASSERT_EQ(C.get<3>(), 154.0); // Row 2: (4*8 + 5*10 + 6*12)
}

TEST_F(ElementMatrixTest, VectorMultiplication)
{
    ElementMatrix<1, 3, double, double, double> A{ 1.0, 2.0, 3.0 };
    ElementMatrix<3, 1, double, double, double> B{ 7.0, 8.0, 9.0 };

    auto C = A * B;

    ASSERT_EQ(C.size, 1);
    ASSERT_EQ(C.n_row, 1);
    ASSERT_EQ(C.n_col, 1);
    ASSERT_EQ(C.get<0>(), 50.0); // dot product: 1*7 + 2*8 + 3*9

    auto D = B * A;

    ASSERT_EQ(D.size, 9);
    ASSERT_EQ(D.n_row, 3);
    ASSERT_EQ(D.n_col, 3);
    ASSERT_EQ(D.get<0>(), 7.0);  // 7*1
    ASSERT_EQ(D.get<1>(), 14.0); // 7*2
    ASSERT_EQ(D.get<2>(), 21.0); // 7*3
    ASSERT_EQ(D.get<3>(), 8.0);  // 8*1
    ASSERT_EQ(D.get<4>(), 16.0); // 8*2
    ASSERT_EQ(D.get<5>(), 24.0); // 8*3
    ASSERT_EQ(D.get<6>(), 9.0);  // 9*1
    ASSERT_EQ(D.get<7>(), 18.0); // 9*2
    ASSERT_EQ(D.get<8>(), 27.0); // 9*3
}

TEST_F(ElementMatrixTest, DotProduct)
{
    ElementMatrix<3, 1, double, double, double> A{ 1.0, 2.0, 3.0 };
    ElementMatrix<3, 1, double, double, double> B{ 4.0, 5.0, 6.0 };

    auto dotProduct = A.dot(B);

    ASSERT_EQ(dotProduct, 32.0); // dot product: 1*4 + 2*5 + 3*6
}

TEST_F(ElementMatrixTest, Transpose)
{
    ElementMatrix<2, 3, double, double, double, double, double, double> A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    auto B = A.transpose();

    ASSERT_EQ(B.size, 6);
    ASSERT_EQ(B.n_row, 3);
    ASSERT_EQ(B.n_col, 2);
    ASSERT_EQ(B.get<0>(), 1.0);
    ASSERT_EQ(B.get<1>(), 4.0);
    ASSERT_EQ(B.get<2>(), 2.0);
    ASSERT_EQ(B.get<3>(), 5.0);
    ASSERT_EQ(B.get<4>(), 3.0);
    ASSERT_EQ(B.get<5>(), 6.0);
}

TEST_F(ElementMatrixTest, Determinant)
{
    ElementMatrix<2, 2, double, double, double, double> A{ 1.0, 2.0, 3.0, 4.0 };

    auto detA = A.determinant();

    ASSERT_EQ(detA, -2.0); // 1*4 - 2*3 = -2

    ElementMatrix<3, 3, double, double, double, double, double, double, double, double, double> B{ 1.0, 2.0, 3.0,
                                                                                                   4.0, 5.0, 6.0,
                                                                                                   7.0, 8.0, 9.0 };

    auto detB = B.determinant();

    ASSERT_EQ(detB, 0.0); // determinant of a singular matrix is zero
}

TEST_F(ElementMatrixTest, Trace)
{
    ElementMatrix<3, 3, double, double, double, double, double, double, double, double, double> A{ 1.0, 2.0, 3.0,
                                                                                                   4.0, 5.0, 6.0,
                                                                                                   7.0, 8.0, 9.0 };

    auto traceA = A.trace();

    ASSERT_EQ(traceA, 15.0); // 1 + 5 + 9 = 15
}

TEST_F(ElementMatrixTest, Norm)
{
    ElementMatrix<3, 1, double, double, double> A{ 3.0, 4.0, 12.0 };

    auto norm = A.norm();

    ASSERT_EQ(norm, 13.0); // sqrt(3^2 + 4^2 + 12^2) = 13
}

TEST_F(ElementMatrixTest, NormP)
{
    ElementMatrix<3, 1, double, double, double> A{ 1.0, 2.0, 3.0 };

    auto norm2 = A.norm<2>();
    ASSERT_EQ(norm2, std::sqrt(14.0)); // sqrt(1^2 + 2^2 + 3^2) = sqrt(14)

    auto norm3 = A.norm<3>();
    ASSERT_EQ(norm3, std::pow(36.0, 1.0 / 3.0)); // (1^3 + 2^3 + 3^3)^(1/3) = (36)^(1/3)
}

TEST_F(ElementMatrixTest, ToTuple)
{
    ElementMatrix<3, 1, double, double, double> A{ 1.0, 2.0, 3.0 };

    auto tuple = A.to_tuple();

    static_assert(std::is_same_v<decltype(tuple), decltype(A)::TupleType>);

    ASSERT_EQ(std::get<0>(tuple), 1.0);
    ASSERT_EQ(std::get<1>(tuple), 2.0);
    ASSERT_EQ(std::get<2>(tuple), 3.0);
}

TEST_F(ElementMatrixTest, Flatten)
{
    ElementMatrix<2, 3, double, double, double, double, double, double> A{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    auto B = A.flatten();

    ASSERT_EQ(B.size, 6);
    ASSERT_EQ(B.n_row, 1);
    ASSERT_EQ(B.n_col, 6);
    ASSERT_EQ(B.get<0>(), 1.0);
    ASSERT_EQ(B.get<1>(), 2.0);
    ASSERT_EQ(B.get<2>(), 3.0);
    ASSERT_EQ(B.get<3>(), 4.0);
    ASSERT_EQ(B.get<4>(), 5.0);
    ASSERT_EQ(B.get<5>(), 6.0);
}

TEST_F(ElementMatrixTest, CombineRows)
{
    ElementMatrix<2, 2, double, double, double, double> A{ 1.0, 2.0, 3.0, 4.0 };
    ElementMatrix<1, 2, double, double> B{ 5.0, 6.0 };

    auto C = A.combine_rows(B);

    ASSERT_EQ(C.size, 6);
    ASSERT_EQ(C.n_row, 3);
    ASSERT_EQ(C.n_col, 2);
    ASSERT_EQ(C.get<0>(), 1.0);
    ASSERT_EQ(C.get<1>(), 2.0);
    ASSERT_EQ(C.get<2>(), 3.0);
    ASSERT_EQ(C.get<3>(), 4.0);
    ASSERT_EQ(C.get<4>(), 5.0);
    ASSERT_EQ(C.get<5>(), 6.0);
}

TEST_F(ElementMatrixTest, CombineColumns)
{
    ElementMatrix<2, 2, double, double, double, double> A{ 1.0, 2.0, 3.0, 4.0 };
    ElementMatrix<2, 1, double, double> B{ 5.0, 6.0 };

    auto C = A.combine_columns(B);

    ASSERT_EQ(C.size, 6);
    ASSERT_EQ(C.n_row, 2);
    ASSERT_EQ(C.n_col, 3);
    ASSERT_EQ(C.get<0>(), 1.0);
    ASSERT_EQ(C.get<1>(), 2.0);
    ASSERT_EQ(C.get<2>(), 5.0);
    ASSERT_EQ(C.get<3>(), 3.0);
    ASSERT_EQ(C.get<4>(), 4.0);
    ASSERT_EQ(C.get<5>(), 6.0);
}