/**
 * licensed to the apache software foundation (asf) under one
 * or more contributor license agreements.  see the notice file
 * distributed with this work for additional information
 * regarding copyright ownership.  the asf licenses this file
 * to you under the apache license, version 2.0 (the
 * "license"); you may not use this file except in compliance
 * with the license.  you may obtain a copy of the license at
 *
 * http://www.apache.org/licenses/license-2.0
 *
 * unless required by applicable law or agreed to in writing, software
 * distributed under the license is distributed on an "as is" basis,
 * without warranties or conditions of any kind, either express or implied.
 * see the license for the specific language governing permissions and
 * limitations under the license.
 */

#include "hurricane/util/StringUtil.h"
#include <cstdlib>
#include <ctime>
#include <cctype>

using std::vector;
using std::string;

vector<string> SplitString(const string& value, char seperator) {
	vector<string> splitedStrings;

    size_t currentPos = 0;
    while ( 1 ) {
        size_t nextPos = value.find(seperator, currentPos);
        if ( nextPos == string::npos ) {
            string currentString = value.substr(currentPos);
            if ( currentString != "" ) {
                splitedStrings.push_back(currentString);
            }

            break;
        }

        string currentString = value.substr(currentPos, nextPos - currentPos);
        splitedStrings.push_back(currentString);
        currentPos = nextPos + 1;
    }

    return splitedStrings;
}

std::string TrimString(const std::string& value) {
	std::string trimmed = value;

	while ( !trimmed.empty() && isblank(trimmed.front()) ) {
		trimmed.erase(trimmed.begin());
	}

	while ( !trimmed.empty() && isblank(trimmed.back()) ) {
		trimmed.erase(trimmed.end() - 1);
	}

	return trimmed;
}

std::string RandomString(const std::string & candidate, int length)
{
    srand(time(0));

    std::string result;
    for ( int index = 0; index != length; ++ index ) {
        int charIndex = rand() % candidate.size();
        result.push_back(candidate[charIndex]);
    }

    return result;
}
