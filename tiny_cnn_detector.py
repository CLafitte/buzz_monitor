#!/usr/bin/env python3
"""
tiny_cnn_bee_detector.py
MVP: Compute MFCCs from a WAV file and classify using a tiny CNN.
"""

import numpy as np
import librosa
import tensorflow as tf
from tensorflow.keras import layers, models
import sys

# -------------------------------
# CNN Definition
# -------------------------------
def build_tiny_cnn(input_shape=(32, 32, 1)):
    model = models.Sequential([
        layers.Conv2D(16, (3, 3), activation='relu', padding='same', input_shape=input_shape),
        layers.MaxPooling2D((2, 2)),
        layers.Conv2D(32, (3, 3), activation='relu', padding='same'),
        layers.MaxPooling2D((2, 2)),
        layers.Flatten(),
        layers.Dense(64, activation='relu'),
        layers.Dense(1, activation='sigmoid')  # output probability of bee
    ])
    model.compile(optimizer='adam',
                  loss='binary_crossentropy',
                  metrics=['accuracy'])
    return model

# -------------------------------
# Feature Extraction
# -------------------------------
def extract_mfcc(wav_path, n_mfcc=32, n_fft=1024, hop_length=512, target_size=(32,32)):
    y, sr = librosa.load(wav_path, sr=16000)  # resample to 16 kHz
    mfcc = librosa.feature.mfcc(y=y, sr=sr, n_mfcc=n_mfcc, n_fft=n_fft, hop_length=hop_length)
    # Normalize
    mfcc = (mfcc - np.mean(mfcc)) / (np.std(mfcc) + 1e-9)
    # Resize to target_size
    mfcc_resized = tf.image.resize(mfcc[np.newaxis, :, :, np.newaxis], target_size)
    return mfcc_resized.numpy()

# -------------------------------
# Inference
# -------------------------------
def predict_bee(model, feature):
    prob = model.predict(feature, verbose=0)[0][0]
    label = "bee" if prob >= 0.5 else "no_bee"
    return label, prob

# -------------------------------
# Main script
# -------------------------------
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python tiny_cnn_bee_detector.py <path_to_wav>")
        sys.exit(1)

    wav_path = sys.argv[1]

    # Extract MFCC features
    features = extract_mfcc(wav_path)

    # Build tiny CNN (weights random; replace with trained model later)
    model = build_tiny_cnn()

    # Predict
    label, confidence = predict_bee(model, features)
    print(f"Prediction: {label} (confidence: {confidence:.2f})")
