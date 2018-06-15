#ifndef INCLUDED_TRADEBOOK
#define INCLUDED_TRADEBOOK

#include <trade.h>
#include <string>
#include <chrono>
#include <map>
#include <stdexcept>
#include <ostream>

namespace tradebook {

struct TradeSummary {
    Trade::Timestamp d_lastTradeTimestamp;
    Trade::Timestamp d_maxTimeGap;
    Trade::Quantity  d_totalVolume;
    double           d_weightedAveragePrice;
    Trade::Price     d_maxPrice;
};

class Tradebook {
  public:
    void insertTrade(const Trade& trade);

    std::chrono::seconds getMaxTimeGap(const std::string& symbol)           const;
    Trade::Quantity      getTotalVolumeTraded(const std::string& symbol)    const;
    Trade::Price         getWeightedAveragePrice(const std::string& symbol) const;
    Trade::Price         getMaxTradedPrice(const std::string& symbol)       const;

    void printSummary(std::ostream& stream) const;
  private:
    std::map<std::string, TradeSummary> d_summary;
};

inline
std::chrono::seconds Tradebook::getMaxTimeGap(const std::string& symbol) const {
    auto it = d_summary.find(symbol);
    if (it == d_summary.end()) {
        throw std::invalid_argument("Symbol " + symbol + " not found");
    } else {
        return std::chrono::duration_cast<std::chrono::seconds>(it->second.d_maxTimeGap);
    }
}

inline
Trade::Quantity Tradebook::getTotalVolumeTraded(const std::string& symbol) const {
    auto it = d_summary.find(symbol);
    if (it == d_summary.end()) {
        throw std::invalid_argument("Symbol " + symbol + " not found");
    } else {
        return it->second.d_totalVolume;
    }
}

inline
Trade::Price Tradebook::getWeightedAveragePrice(const std::string& symbol) const {
    auto it = d_summary.find(symbol);
    if (it == d_summary.end()) {
        throw std::invalid_argument("Symbol " + symbol + " not found");
    } else {
        return static_cast<Trade::Price>(it->second.d_weightedAveragePrice);
    }
}

inline
Trade::Price Tradebook::getMaxTradedPrice(const std::string& symbol) const {
    auto it = d_summary.find(symbol);
    if (it == d_summary.end()) {
        throw std::invalid_argument("Symbol " + symbol + " not found");
    } else {
        return it->second.d_maxPrice;
    }
}

}

#endif