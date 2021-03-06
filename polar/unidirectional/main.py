#!/usr/bin/env python
import lateral
import sagittal


if __name__ == '__main__':
    length = 0

    # inner.set_P()
    # inner = sagittal.Sagittal_Capturability('Biped')
    # while 1:
    #     inner.cal_inner()
    #     if len(inner.P)==length:
    #         break
    #     else :
    #         length = len(inner.P)

    inner = sagittal.Sagittal_Capturability('2d_const', 0.6)
    inner.set_P()
    while 1:
        inner.cal_inner_const()
        if len(inner.P)==length:
            break
        else :
            length = len(inner.P)

    # inner_lateral = lateral.Lateral_Capturability('Biped_lataral')
    # inner_lateral.set_P()
    # while 1:
    #     inner_lateral.cal_inner()
    #     if len(inner_lateral.P)==length:
    #         break
    #     else :
    #         length = len(inner_lateral.P)
