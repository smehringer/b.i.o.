// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2021, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2021, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <sstream>
#include <seqan3/std/concepts>

#include <seqan3/core/debug_stream/byte.hpp>
#include <seqan3/core/debug_stream/optional.hpp>
#include <seqan3/core/debug_stream/tuple.hpp>
#include <seqan3/core/debug_stream/variant.hpp>
#include <seqan3/test/expect_range_eq.hpp>
#include <seqan3/test/pretty_printing.hpp>

template <typename reader_type>
struct reader_test : public ::testing::Test
{};

TYPED_TEST_SUITE_P(reader_test);

TYPED_TEST_P(reader_test, concepts)
{
    EXPECT_TRUE((std::ranges::input_range<typename TestFixture::reader_default_t>));

    // not const-iterable
    EXPECT_FALSE((std::ranges::input_range<typename TestFixture::reader_default_t const>));
}

TYPED_TEST_P(reader_test, constructor1_just_filename)
{
    /* just the filename */
    {
        seqan3::test::tmp_filename filename{"seq_io_reader_constructor.fasta"};
        std::ofstream              filecreator{filename.get_path(), std::ios::out | std::ios::binary};

        EXPECT_NO_THROW((this->construct(filename.get_path())));
    }

    /* non-existent file */
    {
        EXPECT_THROW((bio::seq_io::reader{"/dev/nonexistant/foobarOOO"}),
                     bio::file_open_error);
    }

    /* wrong extension */
    seqan3::test::tmp_filename filename{"seq_io_reader_constructor.xyz"};
    std::ofstream              filecreator{filename.get_path(), std::ios::out | std::ios::binary};
    EXPECT_THROW((bio::seq_io::reader{filename.get_path()}), bio::unhandled_extension_error);

    EXPECT_TRUE((std::same_as<decltype(this->construct("")), typename TestFixture::reader_default_t>));
}

REGISTER_TYPED_TEST_SUITE_P(reader_test,
                            concepts,
                            constructor1_just_filename);
