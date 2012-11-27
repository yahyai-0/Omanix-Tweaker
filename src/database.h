/*
 * Ahmed Al-Yahyai
 * blackheart10001@gmail.com
 * 
 * Omanix Tweaker is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Omanix Tweaker is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
#include <sqlite3.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>

using namespace std;

class SQLiteDB
{
	public:
		SQLiteDB();
	    ~SQLiteDB();

		bool exists(string filename);
		bool open(string fileName);
		void close();
		void finalize();
		int getRC()const;

		vector<string> nextRecord();
		vector<string> query(string q);
	     
	private:
		int rc;
	    sqlite3 *db;
		sqlite3_stmt *ppStmt;

};

#endif // _DATABASE_H_
