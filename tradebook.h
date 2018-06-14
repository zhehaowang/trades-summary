#ifndef INCLUDED_TRADEBOOK
#define INCLUDED_TRADEBOOK

#include <trade.h>
#include <string>
#include <chrono>

namespace tradebook {

class Tradebook {
  public:
    void insertTrade(const Trade& trade);

    Trade::Timestamp getMaximumTimeGap(const std::string& symbol)       const;
    Trade::Quantity  getTotalVolumeTraded(const std::string& symbol)    const;
    Trade::Price     getWeightedAveragePrice(const std::string& symbol) const;
    Trade::Price     getMaxTradedPrice(const std::string& symbol)       const;
  private:

};

}

#endif