import cv2 as cv
import numpy as np
from tests_common import NewOpenCVTests
import utils

## for consistency
np.random.seed(seed=1)
cv.setRNGSeed(seed=1)

transformations = [cv.augment_Resize(size=(1080,1920), interpolations=[cv.INTER_NEAREST, cv.INTER_LINEAR, cv.INTER_AREA, cv.INTER_CUBIC, cv.INTER_LANCZOS4]),
                   cv.augment_Resize(size=(1080,1920), interpolation=cv.INTER_NEAREST),
                   cv.augment_Resize(size=(1080,1920))]

class resizeTest(NewOpenCVTests):
    def test_image(self):
        utils.test_image(transformations)


    def test_point(self):
        utils.test_points(transformations)


    def test_rectangle(self):
        utils.test_rectangles(transformations)


    def test_polygon(self):
        utils.test_polygons(transformations)