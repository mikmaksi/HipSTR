#ifndef REGION_H_
#define REGION_H_

#include <assert.h>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdlib.h>

#include "error.h"

class Region{
private:
  std::string chrom_, name_;
  int32_t start_, stop_;
  std::set<std::string> sample_set_;
  std::map<std::string, std::string> sample_annots_;
  int period_;
public:
  Region(std::string chrom, int32_t start, int32_t stop, int period){
    assert(stop > start);
    chrom_ = chrom; start_ = start; stop_ = stop; period_ = period; name_ = "";
  }

  Region(std::string chrom, int32_t start, int32_t stop, int period, std::string name){
    assert(stop > start);
    chrom_ = chrom; start_ = start; stop_ = stop; period_ = period; name_ = name;
  }

  const std::string& chrom() const { return chrom_;  }
  const std::string& name()  const { return name_;   }
  int32_t start()            const { return start_;  }
  int32_t  stop()            const { return stop_;   }
  int     period()           const { return period_; }
  Region*   copy()           const { return new Region(chrom_, start_, stop_, period_, name_); }

  bool operator<(const Region &r)  const {
    if (chrom_.compare(r.chrom()) != 0)
      return chrom_.compare(r.chrom());
    if (start_ != r.start())
      return start_ < r.start();
    if (stop_ != r.stop())
      return stop_ < r.stop();
    return false;
  }

};

void readRegions(std::string& input_file, std::vector<Region>& regions, uint32_t max_regions);

void orderRegions(std::vector<Region>& regions);

void orderRegions(std::vector<Region>& input_regions, 
		  std::vector< std::vector<Region> >& output_regions, 
		  std::map<std::string, int>& chrom_order);

#endif
