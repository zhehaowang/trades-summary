#include <tradebook.h>

namespace tradebook {

void
Tradebook::insertTrade(const Trade& trade) {
    
}

Trade::Timestamp
Tradebook::getMaximumTimeGap(const std::string& symbol) const {
    Trade::Timestamp result;
    return result;
}

Trade::Quantity
Tradebook::getTotalVolumeTraded(const std::string& symbol) const {
    return 0;
}

Trade::Price
Tradebook::getWeightedAveragePrice(const std::string& symbol) const {
    return 0;
}

Trade::Price
Tradebook::getMaxTradedPrice(const std::string& symbol) const {
    return 0;
}

}