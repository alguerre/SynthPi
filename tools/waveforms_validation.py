import pandas as pd
import matplotlib.pyplot as plt

TEST_PATH = "../build/"
RATE = 44100
count_figures = 0

def create_comparison(waveform_name, reference_name, label):
    comparison = pd.read_csv(TEST_PATH + waveform_name, names=["waveform"])
    reference = pd.read_csv(TEST_PATH + reference_name, names=["data"])
    print(TEST_PATH + waveform_name)
    print(TEST_PATH + reference_name)
    print(reference.head())
    print(comparison.head())

    comparison["reference"] = reference["data"]
    comparison["error"] = comparison["reference"] - comparison["waveform"]

    global count_figures
    count_figures = count_figures + 1

    plt.figure(count_figures)
    plt.subplot(211)
    plt.plot(comparison["waveform"], color='g', linewidth=2.0, label='waveform')
    plt.plot(comparison["reference"], color='b', linewidth=2.0, label='reference')
    plt.legend()

    plt.subplot(212)
    plt.plot(comparison["error"], color='r', linewidth=2.0, label='error')
    plt.legend()

    plt.savefig(label + ".png")



if __name__ == "__main__":
    create_comparison("SineOscillator.csv",
                      "SineReference.csv",
                      "sine_validation")

    create_comparison("SquareOscillator.csv",
                      "SquareReference.csv",
                      "square_validation")

    create_comparison("TriangleOscillator.csv",
                      "TriangleReference.csv",
                      "triangle_validation")

    create_comparison("SawtoothOscillator.csv",
                      "SawtoothReference.csv",
                      "sawtooth_validation")
