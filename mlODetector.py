import numpy as np
import os
from tflite_model_maker.config import QuantizationConfig
from tflite_model_maker.config import ExportFormat
from tflite_model_maker import model_spec
from tflite_model_maker import object_detector

import tensorflow as tf
assert tf.__version__.startswith('2')

tf.get_logger().setLevel('ERROR')
from absl import logging
logging.set_verbosity(logging.ERROR)

spec = model_spec.get('efficientdet_lite0')

train_data, validation_data,test_data = object_detector.DataLoader.from_csv('/home/mbasa/Downloads/4113/train_annotation.csv')
#validation_data= object_detector.DataLoader.from_csv('/home/mbasa/Downloads/4113/test_annotation.csv')
#test_data=object_detector.DataLoader.from_csv('/home/mbasa/Downloads/4113/test_annotation.csv')

#train_data, validation_data, test_data= data.split(0.7)
model = object_detector.create(train_data, model_spec=spec, batch_size=2, train_whole_model=True, validation_data=validation_data)

model.evaluate(test_data)

model.export(export_dir='.')

model.evaluate_tflite('model.tflite', test_data)
