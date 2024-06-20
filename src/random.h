#ifndef SB7_RANDOM_H_
#define SB7_RANDOM_H_

#include "randomc/randomc.h"

namespace sb7 {
	class Random {
		public:
			Random();

			int nextInt();

			int nextInt(int n);

			double nextDouble();

		private:
			TRandomMersenne randomGen;
	};
}

#endif /*SB7_RANDOM_H_*/

