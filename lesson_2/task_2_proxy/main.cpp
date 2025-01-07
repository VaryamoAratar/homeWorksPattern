#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    virtual std::string GetData(const std::string& key) noexcept {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : public VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}

    std::string GetData(const std::string& key)  noexcept override {
        if (cache_.find(key) == cache_.end()) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        }
        else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

class TestDB : public VeryHeavyDatabase { 
public:
    explicit TestDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}

    std::string GetData(const std::string& key)  noexcept override { 
        return "test_data\n";
    }

private:
    VeryHeavyDatabase* real_db_;
};

class OneShotDB : public VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_db_(real_object), limit_(shots), count_(0) {}

    std::string GetData(const std::string& key) noexcept override {
        if (count_ < limit_) {
            count_++;
            return real_db_->GetData(key);
        }
        else {
            return "error";
        }
    }

private:
    VeryHeavyDatabase* real_db_;
    size_t limit_;
    size_t count_;
};

int main() {
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);

    std::cout << limit_db.GetData("key") << std::endl;  
    std::cout << limit_db.GetData("key") << std::endl;  
    std::cout << limit_db.GetData("key") << std::endl;  

    return 0;
}