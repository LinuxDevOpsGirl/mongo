/*    Copyright 2009 10gen Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects
 *    for all of the code used other than as permitted herein. If you modify
 *    file(s) with this exception, you may extend this exception to your
 *    version of the file(s), but you are not obligated to do so. If you do not
 *    wish to do so, delete this exception statement from your version. If you
 *    delete this exception statement from all source files in the program,
 *    then also delete it in the license file.
 */

#include "mongo/bson/bsontypes.h"
#include "mongo/bson/optime.h"

#include <iostream>
#include <limits>
#include <ctime>

#include "mongo/platform/cstdint.h"

namespace mongo {

    OpTime OpTime::max() {
        unsigned int t = static_cast<unsigned int>(std::numeric_limits<int32_t>::max());
        unsigned int i = std::numeric_limits<uint32_t>::max();
        return OpTime(t, i);
    }

    void OpTime::append(BufBuilder& builder, const StringData& fieldName) const {
	// No endian conversions needed, since we store in-memory representation
	// in little endian format, regardless of target endian.
	builder.appendNum( static_cast<char>(Timestamp) );
	builder.appendStr( fieldName );
	builder.appendNum( asDate() );
    }
}