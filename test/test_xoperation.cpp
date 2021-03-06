/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include <cstddef>
#include "xtensor/xarray.hpp"

namespace xt
{
    using std::size_t;
    using shape_type = std::vector<size_t>;

    TEST(operation, plus)
    {
        shape_type shape = {3 ,2};
        xarray<double> a(shape, 4.5);
		double ref = +(a(0, 0));
		double actual = (+a)(0, 0);
        EXPECT_EQ(ref, actual);
    }

    TEST(operation, minus)
    {
        shape_type shape = {3 ,2};
        xarray<double> a(shape, 4.5);
		double ref = -(a(0, 0));
		double actual = (-a)(0, 0);
        EXPECT_EQ(ref, actual);
    }

    TEST(operation, add)
    {
        shape_type shape = {3, 2};
        xarray<double> a(shape, 4.5);
        xarray<double> b(shape, 1.3);
        EXPECT_EQ((a + b)(0, 0), a(0, 0) + b(0, 0));
        
        double sb = 1.2;
        EXPECT_EQ((a + sb)(0, 0), a(0, 0) + sb);

        double sa = 4.6;
        EXPECT_EQ((sa + b)(0, 0), sa + b(0, 0));
    }

    TEST(operation, subtract)
    {
        shape_type shape = {3, 2};
        xarray<double> a(shape, 4.5);
        xarray<double> b(shape, 1.3);
        EXPECT_EQ((a - b)(0, 0), a(0, 0) - b(0, 0));
        
        double sb = 1.2;
        EXPECT_EQ((a - sb)(0, 0), a(0, 0) - sb);

        double sa = 4.6;
        EXPECT_EQ((sa - b)(0, 0), sa - b(0, 0));
    }
    
    TEST(operation, multiply)
    {
        shape_type shape = {3, 2};
        xarray<double> a(shape, 4.5);
        xarray<double> b(shape, 1.3);
        EXPECT_EQ((a * b)(0, 0), a(0, 0) * b(0, 0));
        
        double sb = 1.2;
        EXPECT_EQ((a * sb)(0, 0), a(0, 0) * sb);

        double sa = 4.6;
        EXPECT_EQ((sa * b)(0, 0), sa * b(0, 0));
    }
    
    TEST(operation, divide)
    {
        shape_type shape = {3, 2};
        xarray<double> a(shape, 4.5);
        xarray<double> b(shape, 1.3);
        EXPECT_EQ((a / b)(0, 0), a(0, 0) / b(0, 0));
        
        double sb = 1.2;
        EXPECT_EQ((a / sb)(0, 0), a(0, 0) / sb);

        double sa = 4.6;
        EXPECT_EQ((sa / b)(0, 0), sa / b(0, 0));
    }

    TEST(operation, less)
    {
        xarray<double> a = {1, 2, 3, 4, 5};
        xarray<bool> expected = {1, 1, 1, 0, 0};
        xarray<bool> b = a < 4; 
        EXPECT_EQ(expected, b);
    }

    TEST(operation, less_equal)
    {
        xarray<double> a = {1, 2, 3, 4, 5};
        xarray<bool> expected = {1, 1, 1, 1, 0};
        xarray<bool> b = a <= 4; 
        EXPECT_EQ(expected, b);
    }

    TEST(operation, greater)
    {
        xarray<double> a = {1, 2, 3, 4, 5};
        xarray<bool> expected = {0, 0, 0, 0, 1};
        xarray<bool> b = a > 4;
        EXPECT_EQ(expected, b);
    }

    TEST(operation, greater_equal)
    {
        xarray<double> a = {1, 2, 3, 4, 5};
        xarray<bool> expected = {0, 0, 0, 1, 1};
        xarray<bool> b = a >= 4; 
        EXPECT_EQ(expected, b);
    }

    TEST(operation, negate)
    {
        xarray<double> a = {1, 2, 3, 4, 5};
        xarray<bool> expected = {1, 1, 1, 0, 0};
        xarray<bool> b = !(a >= 4);
        EXPECT_EQ(expected, b);
    }

    TEST(operation, equal)
    {
        xarray<double> a = {1, 2, 3, 4, 5};
        xarray<bool> expected = {0, 0, 0, 1, 0};
        xarray<bool> b = equal(a, 4);
        EXPECT_EQ(expected, b);

        xarray<double> other = {1, 2, 3, 0, 0};
        xarray<bool> b_2 = equal(a, other);
        xarray<bool> expected_2 = {1, 1, 1, 0, 0};
        EXPECT_EQ(expected_2, b_2);
    }

    TEST(operation, not_equal)
    {
        xarray<double> a = { 1, 2, 3, 4, 5 };
        xarray<bool> expected = { 1, 1, 1, 0, 1 };
        xarray<bool> b = not_equal(a, 4);
        EXPECT_EQ(expected, b);

        xarray<double> other = { 1, 2, 3, 0, 0 };
        xarray<bool> b_2 = not_equal(a, other);
        xarray<bool> expected_2 = { 0, 0, 0, 1, 1 };
        EXPECT_EQ(expected_2, b_2);
    }

    TEST(operation, logical_and)
    {
        xarray<bool> a = {0, 0, 0, 1, 0};
        xarray<bool> expected = {0, 0, 0, 0, 0};
        xarray<bool> b = a && 0;
        xarray<bool> c = a && a;
        EXPECT_EQ(expected, b);
        EXPECT_EQ(c, a);
    }

    TEST(operation, logical_or)
    {
        xarray<bool> a = {0, 0, 0, 1, 0};
        xarray<bool> other = {0, 0, 0, 0, 0};
        xarray<bool> b = a || other;
        xarray<bool> c = a || 0;
        xarray<bool> d = a || 1;
        EXPECT_EQ(b, a);
        EXPECT_EQ(c, a);

        xarray<bool>expected = {1, 1, 1, 1, 1};
        EXPECT_EQ(expected, d);
    }

    TEST(operation, any)
    {
        xarray<int> a = {0, 0, 3};
        EXPECT_EQ(true, any(a));
        xarray<int> b = {{0, 0, 0}, {0, 0, 0}};
        EXPECT_EQ(false, any(b));
    }

    TEST(operation, all)
    {
        xarray<int> a = {1, 1, 3};
        EXPECT_EQ(true, all(a));
        xarray<int> b = {{0, 2, 1}, {2, 1, 0}};
        EXPECT_EQ(false, all(b));
    }

    TEST(operation, nonzero)
    {
        xarray<int> a = {1, 0, 3};
        std::vector<xindex> expected = {{0}, {2}};
        EXPECT_EQ(expected, nonzero(a));

        xarray<int> b = {{0, 2, 1}, {2, 1, 0}};
        std::vector<xindex> expected_b = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
        EXPECT_EQ(expected_b, nonzero(b));

        auto c = equal(b, 0);
        std::vector<xindex> expected_c = {{0, 0}, {1, 2}};
        EXPECT_EQ(expected_c, nonzero(c));

        shape_type s = {3, 3, 3};
        xarray<bool> d(s);
        std::fill(d.xbegin(), d.xend(), true);

        auto d_nz = nonzero(d);
        EXPECT_EQ(3 * 3 * 3, d_nz.size());
        xindex last_idx = {2, 2, 2};
        EXPECT_EQ(last_idx, d_nz.back());
    }

    TEST(operation, where_only_condition)
    {
        xarray<int> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        std::vector<xindex> expected = {{0, 0}, {1, 1}, {2, 2}};
        EXPECT_EQ(expected, where(a));
    }
}

