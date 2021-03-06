/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"
#include "xtensor/xtensor.hpp"
#include "test_common.hpp"

namespace xt
{
    using vec_type = std::vector<int>;
    using adaptor_type = xtensor_adaptor<vec_type, 3>;
    using container_type = std::array<std::size_t, 3>;

    TEST(xtensor_adaptor, shaped_constructor)
    {
        {
            SCOPED_TRACE("row_major constructor");
            row_major_result<container_type> rm;
            vec_type v;
            adaptor_type a(v, rm.shape());
            compare_shape(a, rm);
        }

        {
            SCOPED_TRACE("column_major constructor");
            column_major_result<container_type> cm;
            vec_type v;
            adaptor_type a(v, cm.shape(), layout::column_major);
            compare_shape(a, cm);
        }
    }

    TEST(xtensor_adaptor, strided_constructor)
    {
        central_major_result<container_type> cmr;
        vec_type v;
        adaptor_type a(v, cmr.shape(), cmr.strides());
        compare_shape(a, cmr);
    }

    TEST(xtensor_adaptor, copy_semantic)
    {
        central_major_result<container_type> res;
        int value = 2;
        vec_type v(res.size(), value);
        adaptor_type a(v, res.shape(), res.strides());

        {
            SCOPED_TRACE("copy constructor");
            adaptor_type b(a);
            compare_shape(a, b);
            EXPECT_EQ(a.data(), b.data());
        }

        {
            SCOPED_TRACE("assignment operator");
            row_major_result<container_type> r;
            vec_type v2(r.size(), 0);
            adaptor_type c(v2, r.shape());
            EXPECT_NE(a.data(), c.data());
            c = a;
            compare_shape(a, c);
            EXPECT_EQ(a.data(), c.data());
        }
    }

    TEST(xtensor_adaptor, move_semantic)
    {
        central_major_result<container_type> res;
        int value = 2;
        vec_type v(res.size(), value);
        adaptor_type a(v, res.shape(), res.strides());

        {
            SCOPED_TRACE("move constructor");
            adaptor_type tmp(a);
            adaptor_type b(std::move(tmp));
            compare_shape(a, b);
            EXPECT_EQ(a.data(), b.data());
        }

        {
            SCOPED_TRACE("move assignment");
            row_major_result<container_type> r;
            vec_type v2(r.size(), 0);
            adaptor_type c(v2, r.shape());
            EXPECT_NE(a.data(), c.data());
            adaptor_type tmp(a);
            c = std::move(tmp);
            compare_shape(a, c);
            EXPECT_EQ(a.data(), c.data());
        }
    }

    TEST(xtensor_adaptor, reshape)
    {
        vec_type v;
        adaptor_type a(v);
        test_reshape<adaptor_type, container_type>(a);
    }

    TEST(xtensor_adaptor, access)
    {
        vec_type v;
        adaptor_type a(v);
        test_access<adaptor_type, container_type>(a);
    }

    TEST(xtensor_adaptor, indexed_access)
    {
        vec_type v;
        adaptor_type a(v);
        test_indexed_access<adaptor_type, container_type>(a);
    }

    TEST(xtensor_adaptor, broadcast_shape)
    {
        vec_type v;
        xtensor_adaptor<vec_type, 4> a(v);
        test_broadcast(a);
    }

    TEST(xtensor_adaptor, iterator)
    {
        vec_type v;
        adaptor_type a(v);
        test_iterator<adaptor_type, container_type>(a);
    }
}