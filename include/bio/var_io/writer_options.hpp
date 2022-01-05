// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2021, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2021, Knut Reinert & MPI für molekulare Genetik
// Copyright (c) 2020-2021, deCODE Genetics
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

/*!\file
 * \brief Provides bio::var_io::writer_options.
 * \author Hannes Hauswedell <hannes.hauswedell AT decode.is>
 */

#pragma once

#include <bio/format/vcf.hpp>
#include <bio/stream/transparent_ostream.hpp>
#include <bio/var_io/misc.hpp>

namespace bio::var_io
{

/*!\brief Options that can be used to configure the behaviour of bio::var_io::writer.
 * \tparam formats_t     Type of the formats member (usually deduced).
 * \ingroup var_io
 *
 * \details
 *
 * TODO describe how to easily initialise this
 */
template <typename formats_t = seqan3::type_list<vcf>>
struct writer_options
{
    /*!\brief The formats that output files can take; a bio::ttag over the types.
     *
     * \details
     *
     * See bio::var_io::writer for an overview of the the supported formats.
     */
    formats_t formats = ttag<vcf>;

    //!\brief Options that are passed on to the internal stream oject.
    transparent_ostream_options stream_options{};

    /*!\brief Write legacy Windows line-endings including carriage return.
     *
     * \details
     *
     * This option results in old Windows-style line-endings ("\r\n"). Since Windows supports the typical UNIX
     * line-endigns ("\n") nowadays, this option is is highly discouraged.
     *
     * Binary formats always ignore this option.
     */
    bool windows_eol = false;

    /*!\brief Write IDX fields in the header.
     *
     * \details
     *
     * According to the specification for VCF/BCF, entries in the header may be given an IDX value
     * which uniquely identifies that entry¹.
     * Similar to bcftools, the BIO implementation for BCF always writes IDX values.
     * For VCF the default is to not write them (although they are always used internally).
     * This switch turns on writing for VCF, too.
     *
     * ¹ There are two sets of IDX values: one for contigs and one for INFO, FILTER and FORMAT entries (combined).
     */
    bool write_IDX = false;

private:
    static_assert(detail::is_type_list<formats_t>, "formats must be a bio::ttag / seqan3::type_list.");
};

} // namespace bio::var_io