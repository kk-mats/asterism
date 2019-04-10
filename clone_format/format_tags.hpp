#ifndef FORMAT_TAGS_HPP
#define FORMAT_TAGS_HPP

#include <QString>

namespace asterism
{

class format_tags
{
public:
	static inline const QString GLOBAL="global";
	static inline const QString TARGET="target";
	static inline const QString ENVIRONMENT="environment";
	static inline const QString SOURCE="source";
	static inline const QString CLONE_DETECTOR="clone_detector";
	static inline const QString NAME="name";
	static inline const QString PARAMETERS="parameters";
	static inline const QString SIZE="size";
	static inline const QString FILE_TABLE="file_table";
	static inline const QString RESULTS="results";
	static inline const QString CLONE_PAIRS="clone_pairs";
	static inline const QString CLONE_PAIR_SIZE="clone_pair_size";
	static inline const QString RESULT_ID="result_id";
	static inline const QString FILE_ID="file_id";
	static inline const QString PATH="path";
	static inline const QString CLONE_PAIR_ID="clone_pair_id";
	static inline const QString SIMILARITY="similarity";
	static inline const QString FRAGMENT1="fragment1";
	static inline const QString FRAGMENT2="fragment2";
	static inline const QString BEGIN="begin";
	static inline const QString END="end";

};

}

#endif // FORMAT_TAGS_HPP
