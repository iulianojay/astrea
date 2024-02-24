import os
import ctypes as ct
import numpy as np
import numpy.ctypeslib as ctl

# Types
c_int = ct.c_int
c_doub = ct.c_double
c_bool = ct.c_bool
c_doub_p = ct.POINTER(ct.c_double)
c_doub_array = ctl.ndpointer(dtype=np.double, ndim=1, flags='C_CONTIGUOUS')
c_char_p = ct.c_char_p

class AstroLib(object):
    def __init__(self):
        # C++ library
        libname = os.path.join(os.getenv('COMMON_PATH'), 'astro', 'lib', 'libastro.so')
        libastro = ct.CDLL(libname)

        #------------------------------------------- Frame Conversions --------------------------------------------#
        self.c_bci_to_bcbf = libastro.bci_to_bcbf
        self.c_bcbf_to_bci = libastro.bcbf_to_bci
        self.c_bcbf_to_lla = libastro.bcbf_to_lla
        self.c_lla_to_bcbf = libastro.lla_to_bcbf

        self.c_bci_to_bcbf.argtypes = [c_doub_array, c_doub, c_doub, c_doub_array]
        self.c_bcbf_to_bci.argtypes = [c_doub_array, c_doub, c_doub, c_doub_array]
        self.c_bcbf_to_lla.argtypes = [c_doub_array, c_doub, c_doub, c_doub_array]
        self.c_lla_to_bcbf.argtypes = [c_doub_array, c_doub, c_doub, c_doub_array]

        self.c_bci_to_bcbf.restype = None
        self.c_bcbf_to_bci.restype = None
        self.c_bcbf_to_lla.restype = None
        self.c_lla_to_bcbf.restype = None
        
        #---------------------------------------- Element Set Conversions -----------------------------------------#
        self.c_coes_to_bci = libastro.coes_to_bci
        self.c_bci_to_coes = libastro.bci_to_coes
        self.c_mees_to_coes = libastro.mees_to_coes

        self.c_coes_to_bci.argtypes = [c_doub, c_doub, c_doub, c_doub, c_doub, c_doub, c_doub, c_doub_array, c_doub_array]
        self.c_bci_to_coes.argtypes = [c_doub_array, c_doub_array, c_doub, c_doub_array]
        self.c_mees_to_coes.argtypes = [c_doub, c_doub, c_doub, c_doub, c_doub, c_doub, c_doub_array]

        self.c_coes_to_bci.restype = None
        self.c_bci_to_coes.restype = None
        self.c_mees_to_coes.restype = None

        #------------------------------------------- Time Conversions ---------------------------------------------#
        self.c_epoch_to_julian_date = libastro.epoch_to_julian_date
        self.c_julian_date_to_sidereal_time = libastro.julian_date_to_sidereal_time

        self.c_epoch_to_julian_date.argtypes = [c_char_p]
        self.c_julian_date_to_sidereal_time.argtypes = [c_doub, c_doub]

        self.c_epoch_to_julian_date.restype = c_doub
        self.c_julian_date_to_sidereal_time.restype = c_doub

    #------------------------------------------- Frame Conversions --------------------------------------------#
    def bci_to_bcbf(self, rBCI, julianDate, rotRate):
        rBCBF = np.array([0.0]*3, dtype=np.double)
        self.c_bci_to_bcbf(rBCI, julianDate, rotRate, rBCBF)
        return rBCBF

    def bci_to_bcbf(self, rBCBF, julianDate, rotRate):
        rBCI = np.array([0.0]*3, dtype=np.double)
        self.c_bci_to_bcbf(rBCBF, julianDate, rotRate, rBCI)
        return rBCI

    def bcbf_to_lla(self, rBCBF, equitorialRadius, polarRadius):
        lla = np.array([0.0]*3, dtype=np.double)
        self.c_bci_to_bcbf(rBCBF, equitorialRadius, polarRadius, lla)
        return lla

    def lla_to_bcbf(self, lla, equitorialRadius, polarRadius):
        rBCBF = np.array([0.0]*3, dtype=np.double)
        self.c_bci_to_bcbf(lla, equitorialRadius, polarRadius, rBCBF)
        return rBCBF

    #---------------------------------------- Element Set Conversions -----------------------------------------#
    def coes_to_bci(self, h, ecc, inc, w, raan, theta, mu):
        radius = np.array([0.0]*3, dtype=np.double)
        velocity = np.array([0.0]*3, dtype=np.double)
        self.c_coes_to_bci(h, ecc, inc, w, raan, theta, mu, radius, velocity)
        return radius, velocity

    def bci_to_coes(self, radius, velocity, mu):
        coes = np.array([0.0]*6, dtype=np.double)
        self.c_bci_to_coes(radius, velocity, mu, coes)
        return coes

    def mees_to_coes(self, p, f, g, h, k, L, coes):
        coes = np.array([0.0]*6, dtype=np.double)
        self.c_mees_to_coes(p, f, g, h, k, L, coes)
        return coes

    #------------------------------------------- Time Conversions ---------------------------------------------#
    def epoch_to_julian_date(self, epochString):
        julianDate = self.c_epoch_to_julian_date(epochString)
        return julianDate

    def julian_date_to_sidereal_time(self, julianDate, rotRate):
        siderealTime = self.c_julian_date_to_sidereal_time(julianDate, rotRate)
        return siderealTime