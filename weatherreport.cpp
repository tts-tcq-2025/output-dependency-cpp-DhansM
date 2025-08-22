/*#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };
    /// <summary>
    /// This is a stub for a weather sensor. For the sake of testing 
    /// we create a stub that generates weather data and allows us to
    /// test the other parts of this application in isolation
    /// without needing the actual Sensor during development
    /// </summary>
    class SensorStub : public IWeatherSensor {
        int Humidity() const override {
            return 72;
        }

        int Precipitation() const override {
            return 70;
        }

        double TemperatureInC() const override {
            return 26;
        }

        int WindSpeedKMPH() const override {
            return 52;
        }
    };
    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        // precipitation < 20 is a sunny day
        string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
    
    void TestRainy()
    {
        SensorStub sensor;
        string report = Report(sensor);
        cout << report << endl;
        assert(report.find("rain") != string::npos);
    }

    void TestHighPrecipitation()
    {
        // This instance of stub needs to be different-
        // to give high precipitation (>60) and low wind-speed (<50)
        SensorStub sensor;

        // strengthen the assert to expose the bug
        // (function returns Sunny day, it should predict rain)
        string report = Report(sensor);
        assert(report.length() > 0);
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    cout << "All is well (maybe)\n";
}*/


#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
        public:
            virtual double TemperatureInC() const = 0;
            virtual int Precipitation() const = 0;
            virtual int Humidity() const = 0;
            virtual int WindSpeedKMPH() const = 0;
    };

    /// Default stub (kept as-is)
    class SensorStub : public IWeatherSensor {
        int Humidity() const override { return 72; }
        int Precipitation() const override { return 70; }   // high precip
        double TemperatureInC() const override { return 26; } // warm
        int WindSpeedKMPH() const override { return 52; }     // high wind
    };

    /// New stub to EXPOSE the bug:
    /// High precipitation (>=60), warm temp (>25), but LOW wind (<50).
    /// The current buggy logic will return "Sunny Day" in this case.
    class HighPrecipLowWindStub : public IWeatherSensor {
        int Humidity() const override { return 80; }
        int Precipitation() const override { return 80; }   // >=60 (rainy)
        double TemperatureInC() const override { return 27; } // >25
        int WindSpeedKMPH() const override { return 30; }     // <50
    };

    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        // precipitation < 20 is a sunny day
        string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
    
    // Strengthened: use the NEW stub that should imply rain,
    // and assert for "rain" in the description.
    // This will FAIL because the buggy code returns "Sunny Day".
    void TestRainy()
    {
        HighPrecipLowWindStub sensor;
        string report = Report(sensor);
        cout << "TestRainy: " << report << endl;
        assert(report.find("rain") != string::npos);   // should contain "rain"
    }

    // Strengthened: explicitly assert that "Sunny" must NOT appear
    // for high precipitation, and that "rain" SHOULD appear.
    // This will also FAIL with current buggy logic.
    void TestHighPrecipitation()
    {
        HighPrecipLowWindStub sensor;
        string report = Report(sensor);
        cout << "TestHighPrecipitation: " << report << endl;

        // Stronger, behavior-focused assertions:
        assert(report.find("Sunny") == string::npos);  // should not be sunny
        assert(report.find("rain") != string::npos);   // should mention rain
    }
}

void testWeatherReport() {
    cout << "\nWeather report test\n";
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitation();
    cout << "All is well (maybe)\n";
}
